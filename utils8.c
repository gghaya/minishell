/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:21:15 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/02 18:44:24 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char    *is_exitstatus(char *arg)
// {
// 	int i;
// 	char    *s;

// 	i = 0;
// 	s = malloc();

// 	while (arg[i])
// 	{
// 		i++;
// 	}
// 	while (arg[i])
// 	{
// 		if (arg[i]!= '$')
// 		{
// 			arg[i] = 
// 		}
// 		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '?')
// 		{

// 			arg[i+1] = ft_itoa(arg[i+1]);
// 		}
// 		i++;
// 	}
// 	puts(arg);
// 	return (arg);
// }

int	nw_lenght(char*	arg, t_env	*env)
{
	int	i;
	int	start;
	int	len;
	i = 0;
	start = 0;
	len = ft_strlen(arg);

	if (!arg[i])
		return (0);
	while(arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '?')
		{
			len = len - 2 + ft_strlen(ft_itoa(g_status));
			i += 2;
		}
		else if (arg[i] == '$')
		{
			start = ++i;
			while (is_id(arg[i]) == 1)
				i++;
			if (i > start)
			len = len - ft_strlen(ft_substr(arg, start, (i - start))) + ft_strlen(getenv_(ft_substr(arg, start, (i - start)),env)) - 1;
		}
		else
			i++;
	}
	// printf("len : %d\n", len);
	return (len);
}

char	*expandd(char	*s, t_env *env)
{
	int len;
	int	i;
	int	j;
	int	start;
	int	x = 0;
	char	*expnd;
	char	*res;

	i = 0;
	j = 0;
	start = 0;
	len = nw_lenght(s, env);
	res = malloc(sizeof(char) * (len + 1));
	while (s[i])
	{
		if (s[i] != '$' || (s[i] == '$' && !s[i + 1]) || (s[i] == '$' && s[i+1] && s[i + 1] == '$'))
		{
			res[j] = s[i];
			i++;
			j++;
		}
		else if (s[i] == '$' && s[i+1] && s[i + 1] == '?')
		{
			x = 0;
			expnd = ft_itoa(g_status);
			while (expnd[x])
			{
				res[j] = expnd[x];
				x++;
				j++;
			}
			i+=2;
		}
		else if (s[i] == '$')
		{
			start = ++i;
			while (s[i] && is_id(s[i]) == 1)
				i++;
			if (i > start)
			{
				expnd = getenv_(ft_substr(s, start, i - start), env);
				if (expnd != NULL)
				{
					x = 0;
					while (expnd[x])
					{
						res[j] = expnd[x];
						x++;
						j++;
					}
				}
			}
		}
	}
	return (res);
}