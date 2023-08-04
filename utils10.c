/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:00:58 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/04 18:29:24 by gghaya           ###   ########.fr       */
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
	printf("%d\n", i);
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

void	add_final_back(t_final **lst, t_final *new)
{
	t_final	*tmp;

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

t_tmpliste	*help_final(t_final	**fhead, t_tmpliste	*cur, int	len)
{
	t_redirect	*nw;
	t_final		*final;
	int			i;
	// (void)fhead;
	// (void)len;
	i = 0;
	final = new_final(len);
	while (cur && cur->quotes != -2)
	{
		if (cur->arg != NULL && cur->quotes != -1)
			final->cmd[i++] = cur->arg;
		// else if (cur->quotes == -1)
		// 	continue ;
		else if (cur->redct != NULL)
		{
			nw = cur->redct;
			ft_redct_back(&final->rdct, nw);
		}
		// printf("(%s)", cur->arg);
		// puts(cur->arg);
		cur = cur->next;
	}
	final->cmd[len] = NULL;
	add_final_back(fhead, final);
	// printf("*******\n");
	return (cur);
}

void show_final(t_final	*f)
{
	int	i = 0;
	while (f)
	{
		i = 0;
		while (f->cmd[i] != NULL)
		{
			printf("----cmd %d: %s\n", i, f->cmd[i]);
			i++;
		}
		while (f->rdct != NULL)
		{
			printf("**red : %d    %s\n", f->rdct->token,f->rdct->file);
			f->rdct = f->rdct->next;
		}
		f = f->next;
	}
}