/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:17:30 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/02 19:05:08 by gghaya           ###   ########.fr       */
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

	cur = (*tmp);
	while (cur)
	{
		if (ft_strcmp(cur->arg, "") == 0 && cur->quotes == 0)
			ft_deletenode(tmp, cur);
		cur = cur->next;
	}
	free(cur);
}

void	ft_heredoc(t_tmpliste **tmp, t_env	*env)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;
	char		*str;

	cur = (*tmp);
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->arg, "<<") == 0)
		{
			prev = cur;
			cur = cur->next;
			if (cur && cur->quotes == -1)
				cur = cur->next;
			str = strdup("");
			while (cur && (cur->quotes != -2
					&& cur->quotes != -1 && is_token(cur->arg) == 0))
			{
				str = ft_strjoin(str, cur->arg);
				ft_deletenode(tmp, cur);
				cur = cur->next;
			}
			cur = add_node(prev, str);
			if (cur != NULL)
				ft_hendel_heredoc(cur, env);
		}
		else
			cur = cur->next;
	}
}

void	deletesp(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = NULL;
	while (cur)
	{
		if (cur->quotes == -2 || is_token(cur->arg))
		{
			if (prev && prev->quotes == -1)
				ft_deletenode(tmp, prev);
			cur = cur->next;
			if (cur->quotes == -1)
				ft_deletenode(tmp, cur);
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env)
{
	char	*line;
	int		fildes[2];

	pipe(fildes);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, h_doc->arg) == 0)
			break ;
		line = expandd(line, env);
		puts("line");
		puts(line);
		write(fildes[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fildes[1]);
	return (fildes[0]);
}
