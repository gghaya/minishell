/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:21:15 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/03 18:54:54 by gghaya           ###   ########.fr       */
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

int	nw_lenght(char	*arg, t_env	*env)
{
	int	i;
	int	start;
	int	len;
	char	*s = NULL;
	char	*str = NULL;

	i = 0;
	start = 0;
	len = ft_strlen(arg);
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '?')
		{
			s = ft_itoa(g_status);
			len = len - 2 + ft_strlen(s);
			i += 2;
			free(s);
			s = NULL;
		}
		else if (arg[i] == '$')
		{
			start = ++i;
			while (is_id(arg[i]) == 1)
				i++;
			if (i > start)
			{
				s = ft_substr(arg, start, (i - start));
				str = getenv_(s, env);
				len = len - ft_strlen(s) + ft_strlen(str) - 1;
				free(str);
				str = NULL;
			}
		}
		else
			i++;
	}
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
			i += 2;
			free(expnd);
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
					free(expnd);
				}
			}
		}
	}
	res[j] = '\0';
	return (free(s), res);
}

void	ft_join(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = NULL;
	while (cur)
	{
		prev = cur;
		if (cur->quotes != -1 && cur->quotes != -2)
		{
			cur = cur->next;
			while (cur && (cur->quotes != -1 && cur->quotes != -2 && is_token(cur->arg) == 0))
			{
				prev->arg = ft_strjoin(prev->arg, cur->arg);
				ft_deletenode(tmp, prev->next);
				cur = prev->next;
			}
		}
		else
			cur = cur->next;
	}
}

void collect_red(t_tmpliste	**tmp)
{
	t_tmpliste	*cur;
	int	i = 0;

	cur = (*tmp);
	while (cur)
	{
		if (cur->arg[0] == '>' || cur->arg[0] == '<')
		{
			if (cur->arg[1] == '>' || cur->arg[1] == '<')
			{
				cur->redct = ft_rednw(get_token(ft_substr(cur->arg, 0, 2)));
				i = 2;
			}
			else
			{
				cur->redct = ft_rednw(get_token(ft_substr(cur->arg, 0, 1)));
				i = 1;
			}
			// cur->redct->file = ft_substr(cur->arg, i, ft_strlen(cur->arg));
			free(cur->arg);
			cur->arg = NULL;
			cur = cur->next;
		}
		else
			cur = cur->next;
	}
}

int	get_token(char	*s)
{
	if (ft_strcmp(s, ">>") == 0)
		return (free(s), 0);
	else if (ft_strcmp(s, ">") == 0)
		return (free(s), 1);
	else if (ft_strcmp(s, "<") == 0)
		return (free(s), 2);
	else if (ft_strcmp(s, "<<") == 0)
		return (free(s), 3);
	return (free(s), -1);
}
