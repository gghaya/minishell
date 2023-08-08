/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:21:15 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 11:51:00 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nw_lenght(char	*arg, t_env	*env)
{
	t_s	*s;
	int	len;

	s = malloc(sizeof(t_s));
	s->i = 0;
	s->start = 0;
	s->len = ft_strlen(arg);
	if (!arg)
		return (-1);
	while (arg[s->i])
	{
		if (arg[s->i] == '$' && arg[s->i + 1] && arg[s->i + 1] == '?')
			s->i = do_1(s);
		else if (arg[s->i] == '$')
			s->i = do_2(s, arg, env);
		else
			s->i++;
	}
	len = s->len;
	return (free(s), len);
}

char	*expandd(char	*s, t_env *env)
{
	t_ex	*ex;
	char	*res;

	ex = malloc(sizeof(t_ex));
	ex->i = 0;
	ex->j = 0;
	ex->start = 0;
	ex->len = nw_lenght(s, env);
	ex->res = malloc(sizeof(char) * (ex->len + 1));
	if (!ex->res)
		return (NULL);
	while (s[ex->i])
	{
		if (s[ex->i] != '$' || (s[ex->i] == '$' && !s[ex->i + 1])
			|| (s[ex->i] == '$' && s[ex->i + 1] && s[ex->i + 1] == '$'))
			ex->res[ex->j++] = s[ex->i++];
		else if (s[ex->i] == '$' && s[ex->i + 1] && s[ex->i + 1] == '?')
			expand_1(ex);
		else if (s[ex->i] == '$')
			expand_2(ex, s, env);
	}
	ex->res[ex->j] = '\0';
	res = ex->res;
	return (free(s), free(ex), res);
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
			while (cur && (cur->quotes != -1 && cur->quotes != -2
					&& is_token(cur->arg) == 0))
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

void	collect_red(t_tmpliste	**tmp)
{
	t_tmpliste	*cur;
	int			i;

	i = 0;
	cur = (*tmp);
	while (cur)
	{
		if ((cur->arg[0] == '>' || cur->arg[0] == '<'))
		{
			if (cur->arg[1] == '>' || cur->arg[1] == '<')
			{
				cur->redct = ft_rednw(get_token(ft_substr(cur->arg, 0, 2)));
				i = 2;
			}
			else
				i = collect_help(&cur, cur->arg);
			cur->redct->file = ft_substr(cur->arg, i, ft_strlen(cur->arg));
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
		return (free(s), APPEND);
	else if (ft_strcmp(s, ">") == 0)
		return (free(s), IN);
	else if (ft_strcmp(s, "<") == 0)
		return (free(s), OUT);
	else if (ft_strcmp(s, "<<") == 0)
		return (free(s), HEREDOC);
	return (free(s), -1);
}
