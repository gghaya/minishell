/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:20:33 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 19:00:52 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_tmpliste **begin_list)
{
	t_tmpliste	*cur;
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	cur = *begin_list;
	j = 0;
	while (cur)
	{
		if (cur->quotes == 0)
		{
			tmp = cur->arg;
			cur->arg = ft_check_cmd(tmp, &i);
			cur->redirect = ft_check_redirect(tmp, cur->redirect, &i); 
			free(tmp);
			j++;
			i = 0;
		}
		cur = cur->next;
	}
}

bool	ft_help(t_tmpliste *liste)
{
	char	*input;

	input = readline("Minishell> ");
	add_history(input);
	if (balanced_quotes(input))
	{
		liste = ft_splt(input);
		ft_deletespace(&liste);
		ft_redirection(&liste);
		// if (syntax_error(liste) == 0)
		// 	return (0);
		// else
		// fix_redirection(&liste);
		// delete_empty(&liste);
		ft_print(liste);
	}
	return (1);
}

int	not_in(char *string, char c)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_token(char *string)
{
	if (ft_strcmp(string, ">>") == 0 || ft_strcmp(string, "<<") == 0)
		return (1);
	else if (ft_strcmp(string, ">") == 0 || ft_strcmp(string, "<") == 0)
		return (1);
	return (0);
}

t_tmpliste	*add_node(t_tmpliste *prev, char *content)
{
	t_tmpliste	*node;
	t_tmpliste	*tmp;

	if (!prev)
		return (NULL);
	node = ft_lstnw(content, 0);
	tmp = prev->next;
	prev->next = node;
	node->next = tmp;
	return (node);
}
