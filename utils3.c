/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:20:33 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/07 17:50:50 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_tmpliste **begin_list, int k)
{
	t_tmpliste	*cur;
	int			i;
	char		*tmp;

	cur = *begin_list;
	i = 0;
	while (cur)
	{
		if (cur->quotes == 0)
		{
			tmp = cur->arg;
			cur->arg = ft_check_cmd(tmp, &i);
			cur = ft_check_redirect(tmp, cur, &i, k);
			free(tmp);
			i = 0;
		}
		cur = cur->next;
	}
	free(cur);
}

bool	ft_help(char	*input, t_env	*env)
{
	int			k;
	t_tmpliste	*liste;

	k = 0;
	liste = NULL;
	add_history(input);
	if (balanced_quotes(input))
	{
		liste = ft_splt(input);
		free(input);
		ft_deletespace(&liste);
		ft_redirection(&liste, k);
		delete_empty(&liste);
		if (syntax_error(liste) == 0 || red_error(liste) == -1)
			return (ft_stclear(&liste, free), 0);
		else
			ft_help1(liste, env);
		ft_stclear(&liste, free);
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
	else if (ft_strcmp(string, "><") == 0 || ft_strcmp(string, "<>") == 0)
		return (-1);
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
