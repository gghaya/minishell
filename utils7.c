/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:20 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/01 21:55:52 by gghaya           ###   ########.fr       */
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

char	*fill_arg(char	*arg, char	**substring, int *len, int klen)
{
	int		i;
	char	*res = malloc (sizeof (char) * (len[0] - len[1] + klen + 1));
		if(!res)
			return (NULL);
	int		j;
	i = 0;
	j = 0;
	printf("%d____%d\n",len[0], len[1]);
	while (arg[i])
	{
		if (arg[i] && arg[i] != '$')
		{
			ft_memcpy(res + ft_strlen(res), ft_strdup(&arg[i]), 1);
			i++;
		}
		else if (arg[i] && arg[i] == '$')
		{
			i++;
			if ((!arg[i]|| arg[i] == '$'))
				ft_memcpy(res + ft_strlen(res), ft_strdup(&arg[i]), 1);
			else
			{
			while (arg[i] && is_id(arg[i]) == 1)
				i++;
			if (substring[j] != NULL)
			{
				ft_memcpy(res + ft_strlen(res), substring[j], ft_strlen(substring[j]));
			}
				puts(substring[j]);
			j++;
			}
		}
	}
	return (res);
}

char	*expand(char	*arg, t_env	*env)
{
	int		i;
	int		start;
	char	**substring = NULL;
	char	*key = NULL;
	int		j;
	int	*len = without_dollar(arg);
	int	klen = 0;
	i = 0;
	start = -1;
	j = 0;

	substring =  malloc(sizeof(char *)*(len[1] + 1));
	substring[len[1]] = NULL;
	while (arg[i])
	{
		if (arg[i] && arg[i] == '$' && arg[i + 1] && arg[i+ 1] != '$')
		{
			start = (++i);
			while (arg[i] && is_id(arg[i]) == 1)
				i++;
			if(i == start)
				break;
			key = ft_substr(arg, start, i - start);
			substring[j] = getenv_(key, env);
			if (substring[j] != NULL)
				klen = klen + ft_strlen(substring[j]);
			j++;
		}
		else
			i++;
	}
	return (fill_arg(arg, substring, len, klen));
}

void	ft_expanding(t_tmpliste **tmp, t_env	*env)
{
	t_tmpliste	*cur;

	cur = (*tmp);
	while (cur)
	{
		if (cur->quotes == 0 || cur->quotes == 2)
		{
			// s = ft_strdup(cur->arg);
			// free(cur->arg);
			cur->arg = expand(cur->arg, env);
			// free(s);
		}
		cur = cur->next;
	}
}

int	*without_dollar(char	*s)
{
	int	i;
	int	*len =malloc(2*sizeof(int));

	i = 0;
	len[0] = 0;//number of caracteres without $
	len[1] = 0;//number of $
	while (s[i] != '\0')
	{
		if (s[i] && s[i] == '$')
		{
			if (s[i+1] && s[i + 1]!= '$')
				len[1]++;
			else
				len[0]++;
			i++;
			while (s[i] && is_id(s[i]) == 1)
				i++;
		}
		else
		{
			i++;			
			len[0]++;
		}
	}
	return (len);
}
