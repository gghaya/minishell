/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:30:50 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 15:28:59 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*fill_env(char	**envp)
{
	t_env	*env;
	t_env	*begin_env;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	begin_env = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env = ft_envnw(ft_substr(envp[i], 0, j));
		start = ++j;
		while (envp[i][j] && envp[i][j] != '\0')
			j++;
		env->value = ft_substr(envp[i], start, j - start);
		ft_add_env(&begin_env, env);
		i++;
	}
	return (begin_env);
}

t_final	*ft_help1(t_tmpliste *liste, t_env *env)
{
	t_final	*f;

	deletesp(&liste);
	ft_heredoc(&liste, env);
	ft_expanding(&liste, env);
	ft_join(&liste);
	collect_red(&liste);
	f = fill_final(&liste);
	show_final(f);
	return (f);
}

int	collect_help(t_tmpliste	**cur, char	*s)
{
	(*cur)->redct = ft_rednw(get_token(ft_substr(s, 0, 1)));
	return (1);
}

t_tmpliste	*rm(t_tmpliste **begin_list, t_tmpliste *node)
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
			return (prev->next);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

t_redirect	*ft_rednw(int token)
{
	t_redirect	*list;

	list = (t_redirect *)malloc(sizeof(t_redirect));
	if (!list)
		return (NULL);
	list->token = token;
	list->file = NULL;
	list->next = NULL;
	return (list);
}
