/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:44:18 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 11:58:38 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_1(t_s *s)
{
	s->s = ft_itoa(g_status);
	s->len = s->len - 2 + ft_strlen(s->s);
	s->i += 2;
	free(s->s);
	s->s = NULL;
	return (s->i);
}

int	do_2(t_s *s, char	*arg, t_env *env)
{
	s->start = ++s->i;
	while (is_id(arg[s->i]) == 1)
		s->i++;
	if (s->i > s->start)
	{
		s->s = ft_substr(arg, s->start, (s->i - s->start));
		s->str = getenv_(s->s, env);
		s->len = s->len - ft_strlen(s->s) + ft_strlen(s->str) - 1;
		free(s->str);
		s->str = NULL;
	}
	return (s->i);
}

int	expand_1(t_ex	*ex)
{
	ex->x = 0;
	ex->expnd = ft_itoa(g_status);
	while (ex->expnd[ex->x])
		ex->res[ex->j++] = ex->expnd[ex->x++];
	ex->i += 2;
	free(ex->expnd);
	return (ex->i);
}

int	expand_2(t_ex	*ex, char	*s, t_env	*env)
{
	ex->start = ++ex->i;
	while (s[ex->i] && is_id(s[ex->i]) == 1)
		ex->i++;
	if (ex->i > ex->start)
	{
		ex->expnd = getenv_(ft_substr(s, ex->start, ex->i - ex->start), 
				env);
		if (ex->expnd != NULL)
		{
			ex->x = 0;
			while (ex->expnd[ex->x])
				ex->res[ex->j++] = ex->expnd[ex->x++];
			free(ex->expnd);
		}
	}
	return (ex->i);
}

t_tmpliste	*help_final(t_final	**fhead, t_tmpliste	*cur, int len)
{
	t_redirect	*nw;
	t_final		*final;
	int			i;

	i = 0;
	final = new_final(len);
	while (cur && cur->quotes != -2)
	{
		if (cur->arg != NULL && cur->quotes != -1)
			final->cmd[i++] = cur->arg;
		else if (cur->redct != NULL)
		{
			nw = cur->redct;
			ft_redct_back(&final->rdct, nw);
		}
		cur = cur->next;
	}
	final->cmd[len] = NULL;
	add_final_back(fhead, final);
	return (cur);
}
