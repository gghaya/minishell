/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:20 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 11:46:02 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_id(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*getenv_(char	*key, t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (free(key), ft_strdup(env->value));
		env = env->next;
	}
	return (free(key), NULL);
}

void	ft_expanding(t_tmpliste **tmp, t_env	*env)
{
	t_tmpliste	*cur;

	cur = (*tmp);
	if (!cur)
		return ;
	while (cur)
	{
		if (cur->quotes == 0 || cur->quotes == 2)
			cur->arg = expandd(cur->arg, env);
		cur = cur->next;
	}
}

void	ft_envclear(t_env **lst, void (*del)(void*))
{
	t_env	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->key);
		del((*lst)->value);
		free((*lst));
		(*lst) = p;
	}
	free(*lst);
}

t_tmpliste	*rm_node(t_tmpliste **begin_list, t_tmpliste *node)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = *begin_list;
	prev = NULL;
	if (cur == node)
	{
		*begin_list = node->next;
		free(node->arg);
		free(node);
		return (NULL);
	}
	while (cur != NULL)
	{
		if (cur == node)
		{
			prev->next = cur->next;
			free(cur->arg);
			free(cur);
			return (prev);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}
