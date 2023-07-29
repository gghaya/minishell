/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:09:34 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 16:54:32 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handel_pipe(t_tmpliste *tmp)
{
	t_tmpliste	*cur;

	cur = tmp;
	if (cur != NULL && cur->quotes == -2)
		return (0);
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

bool	 syntax_error(t_tmpliste *tmp)
{
	if (handel_pipe(tmp) == 0)
	{
		printf("minishell: Syntax Error\n");
		return (0);
	}
	return (1);
}

void	ft_red1(char	*arg, int	*i, t_red	**red)
{
	int		k;
	t_red	*node;

	k = 0;
	if (arg[*i] == '>' || arg[*i] == '<')
	{
		(*i)++;
		if (arg[(*i)] && (arg[*i] == '>' || arg[*i] == '<'))
		{
			node = ft_rednw(ft_substr(arg, (*i) - 1, 2));
			k = ++(*i);
		}
		else
		{
			node = ft_rednw(ft_substr(arg, (*i) - 1, 1));
			k = (*i);
		}
		while (arg[(*i)] && not_in("|><", arg[(*i)]) == 0)
			(*i)++;
		node->file = ft_substr(arg, k, (*i) - k);
		ft_red_back(red, node);
	}
	else
		(*i)++;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
