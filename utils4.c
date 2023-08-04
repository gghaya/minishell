/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:09:34 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/04 12:09:46 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handel_pipe(t_tmpliste *tmp)
{
	t_tmpliste	*cur;

	cur = tmp;
	if (cur != NULL && cur->quotes == -2)
		return (0);
	return (help_syntax(cur, tmp));
}

bool	help_syntax(t_tmpliste *cur, t_tmpliste *tmp)
{
	while (cur)
	{
		if (cur->quotes == -2)
		{
			cur = cur->next;
			if ((cur == NULL || cur->quotes == -2)
				|| (cur->quotes == -1 && cur->next->quotes == -2))
				return (0);
		}
		else if (is_token(tmp->arg) == 1)
		{
			tmp = tmp->next;
			if (tmp && tmp->quotes == -1)
				tmp = tmp->next;
			if ((!tmp) || ((is_token(tmp->arg) == 1 || tmp->quotes == -2)))
				return (0);
		}
		else
		{
			cur = cur->next;
			tmp = cur;
		}
	}
	return (1);
}

bool	syntax_error(t_tmpliste *tmp)
{
	if (handel_pipe(tmp) == 0)
	{
		g_status = 258;
		printf("minishell: Syntax Error\n");
		return (0);
	}
	return (1);
}

t_tmpliste	*ft_red1(char	*arg, int	*i, t_tmpliste	*red, int k)
{
	t_tmpliste	*node;

	node = NULL;
	if (arg[*i] && (arg[*i] == '>' || arg[*i] == '<'))
	{
		(*i)++;
		if (arg[(*i)] && (arg[*i] == '>' || arg[*i] == '<'))
		{
			node = add_node(red, ft_substr(arg, (*i) - 1, 2));
			k = ++(*i);
		}
		else
		{
			node = add_node(red, ft_substr(arg, (*i) - 1, 1));
			k = (*i);
		}
		while (arg[(*i)] && not_in("|><", arg[(*i)]) == 0)
			(*i)++;
		if ((*i) > k)
			node = add_node(node, ft_substr(arg, k, (*i) - k));
	}
	return (node);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
