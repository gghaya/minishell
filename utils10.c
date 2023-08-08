/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:00:58 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 12:02:53 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redct_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_final	*fill_final(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_final		*fhead;
	int			len;

	cur = (*tmp);
	fhead = NULL;
	len = cmd_len(cur);
	while (cur)
	{
		cur = help_final(&fhead, cur, len);
		if (cur != NULL)
			cur = cur->next;
		else
			return (fhead);
		len = cmd_len(cur);
	}
	return (fhead);
}

int	cmd_len(t_tmpliste	*prev)
{
	t_tmpliste	*cur;
	int			i;

	i = 0;
	cur = prev;
	while (cur && (cur->quotes != -2))
	{
		if (cur->arg != NULL && cur->quotes != -1 && cur->quotes != -1)
			i++;
		cur = cur->next;
	}
	return (i);
}

t_redirect	*copy_red(int token, char	*file)
{
	t_redirect	*list;

	list = (t_redirect *)malloc(sizeof(t_redirect));
	if (!list)
		return (NULL);
	list->token = token;
	list->file = file;
	list->next = NULL;
	return (list);
}

t_final	*new_final(int len)
{
	t_final	*list;

	list = (t_final *)malloc(sizeof(t_final));
	if (!list)
		return (NULL);
	list->cmd = malloc(sizeof(char *) * (len + 1));
	list->rdct = NULL;
	list->next = NULL;
	return (list);
}
