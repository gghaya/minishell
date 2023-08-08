/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:56:11 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 16:40:31 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	red_error(t_tmpliste	*liste)
{
	t_tmpliste	*cur;

	cur = liste;
	while (cur)
	{
		if (is_token(cur->arg) == -1)
		{
			g_status = 258;
			printf("minishell: Syntax Error\n");
			return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

void	show_final(t_final	*f)
{
	int	i;

	i = 0;
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
			printf("**red : %d    %s\n", f->rdct->token, f->rdct->file);
			f->rdct = f->rdct->next;
		}
		f = f->next;
	}
}
