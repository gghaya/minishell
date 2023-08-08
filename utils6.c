/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:17:30 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 16:48:44 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tmpliste	*ft_splt(char *s)
{
	int			i;
	t_tmpliste	*head;

	head = NULL;
	s = ft_strtrim(s, " \t");
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '|')
			ft_spacepipe(&head, s, &i);
		else if (s[i] == '\'' || s[i] == '\"')
			ft_quotes(&head, s, &i);
		else
			ft_string(&head, s, &i);
		i++;
	}
	free (s);
	return (head);
}

void	delete_empty(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = cur;
	while (cur)
	{
		if ((cur->next) && ft_strcmp(cur->next->arg, "") == 0
			&& cur->next->quotes == 0)
			cur = rm_node(tmp, cur->next);
		else
			cur = cur->next;
		prev = cur;
	}
}

void	ft_heredoc(t_tmpliste **tmp, t_env	*env)
{
	t_strct	s;

	s.cur = (*tmp);
	while (s.cur)
	{
		if (ft_strcmp(s.cur->arg, "<<") == 0)
		{
			s.prev = s.cur;
			s.cur = s.cur->next;
			if (s.cur && s.cur->quotes == -1)
				s.cur = s.cur->next;
			s.str = strdup("");
			while (s.cur && (s.cur->quotes != -2
					&& s.cur->quotes != -1 && is_token(s.cur->arg) == 0))
			{
				s.str = ft_strjoin(s.str, s.cur->arg);
				s.cur = rm_node(tmp, s.cur);
			}
			s.cur = add_node(s.prev, s.str);
			if (s.cur != NULL)
				ft_hendel_heredoc(s.cur, env);
		}
		else
			s.cur = s.cur->next;
	}
}

void	deletesp(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = cur;
	while (cur)
	{
		prev = cur;
		if (cur->quotes == -1 && cur->next && (is_token(cur->next->arg) == 1
				|| cur->next->quotes == -2))
			cur = rm(tmp, cur);
		else if (cur->quotes == -2 || is_token(cur->arg) == 1)
		{
			if ((cur->next) && cur->next->quotes == -1)
				cur = rm(tmp, cur->next);
			else
				cur = cur->next;
		}
		else
			cur = cur->next;
	}
}

// int	ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env)
// {
// 	char	*line;
// 	int		fildes[2];

// 	pipe(fildes);
// 	while (1)
// 	{
// 		line = readline(">");
// 		if (ft_strcmp(line, h_doc->arg) == 0 || line == NULL)
// 			break ;
// 		line = expandd(line, env);
// 		write(fildes[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(line);
// 	close(fildes[1]);
// 	return (fildes[0]);
// }

void handle(int sig)
{
	(void)sig;
	printf("\n");
	exit(0);
}

int	ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env)
{
	char	*line;
	int		fildes[2];
	int ret = -1;
	int		pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &handle);
		pipe(fildes);
		while (1)
		{
			line = readline(">");
			if (ft_strcmp(line, h_doc->arg) == 0 || line == NULL)
			{
				free(line);
				close(fildes[1]);
				exit (fildes[0]);
			}
			line = expandd(line, env);
			write(fildes[1], line, ft_strlen(line));
			printf("%s\n", line);
			free(line);
		}
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, &c_handler);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}
