/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 13:40:52 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int main (int ac , char **av, char **envp)
{
	t_tmpliste *liste=NULL;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		ft_help(liste);
	}
	return (0);
}

/*
1. if there is a token on its own -> syntax error
2. for only pipe: you should not start with a pipe
3. token followed by another token -> s.e. (except pipe followed by redirections)
4. token followed by '\0' ->s.e.
*/

bool	handel_pipe(t_tmpliste *tmp)
{
	t_tmpliste	*cur;

	cur = tmp;
	while (cur)
	{
		if (cur->quotes == -2)
		{
			cur = cur->next;
			if (cur == NULL || cur->quotes == -2)
				return (0);
			if (cur->quotes == -1 && cur->next->quotes == -2)
				return (0);
		}
		else if (handel_redirection(cur->redirect) == 0)
			return (0);
		else
			cur = cur->next;
	}
	return (1);
}

bool	handel_redirection(t_red *tmp_red)
{
	while (tmp_red)
	{
		if ((is_token(tmp_red->token) == 1)
			&& (ft_strcmp(tmp_red->file, "") == 0
			|| ((tmp_red->next) && ft_strcmp(tmp_red->next->token, "|") == 0)))
			return (0);
		else if (tmp_red->token && is_token(tmp_red->token) == 0)
			return (0);
		tmp_red = tmp_red->next;
	}
	return (1);
}

bool	syntax_error(t_tmpliste *tmp)
{
	if (handel_pipe(tmp) == 0)
	{
		printf("minishell: Syntax Error\n");
		return (0);
	}
	return (1);
}