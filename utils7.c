/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:20 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/31 23:18:57 by gghaya           ###   ########.fr       */
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
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*fill_arg(char	*arg, char	**substring, char	**key)
{
	int		i;
	int		start;
	char	*res = malloc (sizeof (char) * 10);
	int		j;
	(void)key;
	i = 0;
	start = 0;
	j = 0;
	// while (arg[i] && arg[i] != '$')
	// 	i++;
	// // puts(arg + i);
	// if (i > start)
	// {
	// 	ft_memcpy(res, arg, i);
	// 	i++;
	// }
	// printf("%d\n",i);
	// puts(res);
	// while (substring[j])
	// {
	// 	puts(substring[j]);
	// // 	j++;
	// // }
	// puts("**");
	while (arg[i])
	{
		start = i;
		while(arg[i] && arg[i] != '$')
			i++;
		if(i > start)
			ft_memcpy(res + start, ft_substr(arg, start, i - start), i - start);
		start = i;
		while (arg[i] && is_id(arg[i]) == 1)
			i++;
		if (substring[j] != NULL)
		{
			puts(substring[0]);
			ft_memcpy(res + start, substring[j], ft_strlen(substring[j]));
			puts("res: ");
			puts(res);
			printf("j  %d\n", j);
			j++;
		}
		else
			i++;
	}
	puts("fin :");
	puts(res);
	return (res);
}

char	*expand(char	*arg, t_env	*env)
{
	int		i;
	int		start;
	char	**substring = NULL;
	char	**keys = NULL;
	int		j;
	int	len = 0;

	i = 0;
	start = -1;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			len++;
		i++;
	}
	i = 0;
	keys = malloc(sizeof(char *)*(len + 1));
	substring =  malloc(sizeof(char *)*(len + 1));
	while (arg[i])
	{
		if (arg[i] && arg[i] == '$')
		{
			start = (++i);
			while (arg[i] && is_id(arg[i]) == 1)
				i++;
			keys[j] = ft_substr(arg, start, i - start);
			substring[j] = getenv_(keys[j], env);
			j++;
		}
		i++;
	}
	if ((size_t)i == ft_strlen(arg))
		keys[j] = arg;
	// exit(0);
	return (fill_arg(arg, substring, keys));
}

void	ft_expanding(t_tmpliste **tmp, t_env	*env)
{
	t_tmpliste	*cur;

	cur = (*tmp);
	while (cur)
	{
		if (cur->quotes == 0 || cur->quotes == 2)
			cur->arg = expand(cur->arg, env);
		cur = cur->next;
	}
}
