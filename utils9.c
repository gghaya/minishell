/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:30:50 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/03 23:34:28 by gghaya           ###   ########.fr       */
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

void	ft_help1(t_tmpliste *liste, t_env *env)
{
	deletesp(&liste);
	ft_heredoc(&liste, env);
	ft_expanding(&liste, env);
	ft_join(&liste);
	collect_red(&liste);
	ft_print(liste);
}