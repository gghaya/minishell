/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:21:20 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/04 11:42:36 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spacepipe(t_tmpliste **head, char *s, int *i)
{
	t_tmpliste	*liste;
	char		*ss;

	liste = NULL;
	ss = ft_substr(s, *i, 1);
	if (s[*i] == ' ')
		liste = ft_lstnw(ft_strdup(ss), -1);
	else if (s[*i] == '|')
		liste = ft_lstnw(ft_strdup(ss), -2);
	free(ss);
	ft_lstad_back(head, liste);
}

void	ft_deletenode(t_tmpliste **begin_list, t_tmpliste *node)
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
		return ;
	}
	while (cur != NULL)
	{
		if (cur == node)
		{
			prev->next = cur->next;
			free(cur->arg);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_quotes(t_tmpliste **head, char *s, int *i)
{
	int			start;
	t_tmpliste	*liste;

	liste = NULL;
	start = (*i)++;
	while (s[*i] != s[start] && s[*i])
		(*i)++;
	if (s[start] == '\'')
		liste = ft_lstnw(ft_substr(s, start + 1, *i - start - 1), 1);
	else
		liste = ft_lstnw(ft_substr(s, start + 1, *i - start - 1), 2);
	ft_lstad_back(head, liste);
}

void	ft_string(t_tmpliste **head, char *s, int *i)
{
	t_tmpliste	*liste;
	int			start;

	liste = NULL;
	start = *i;
	while (s[*i] != ' ' && s[*i] != '|' && s[*i] != '\0' && s[*i] != '\''
		&& s[*i] != '\"')
		(*i)++;
	liste = ft_lstnw(ft_substr(s, start, (*i) - start), 0);
	ft_lstad_back(head, liste);
	(*i)--;
}

void	ft_stclear(t_tmpliste **lst, void (*del)(void*))
{
	t_tmpliste	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->arg);
		free((*lst));
		(*lst) = p;
	}
	free(*lst);
}
