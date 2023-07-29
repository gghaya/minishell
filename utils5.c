/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:12:40 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 18:28:24 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_cmd(char *arg, int	*i)
{
	int		start;
	char	*cmd;

	start = (*i);
	while ((arg[*i] && arg[*i] != '>' && arg[*i] != '<'))
		(*i)++;
	cmd = ft_substr(arg, start, (*i) - start);
	return (cmd);
}

t_red	*ft_check_redirect(char	*arg, t_red	*red, int	*i)
{
	while (arg[*i])
		ft_red1(arg, i, &red);
	return (red);
}

void	ft_print(t_tmpliste *t)
{
	while (t != NULL)
	{
		printf("command (%s) quote (%d)\n", t->arg, t->quotes);
		while (t->redirect != NULL)
		{
			printf ("	**redirection : (%s) file : (%s) FILE_QUOTES : %d\n",
				t->redirect->token, t->redirect->file, t->redirect->fquotes);
			t->redirect = t->redirect->next;
		}
		t = t->next;
	}
	return ;
}

void	ft_deletespace(t_tmpliste **begin_list)
{
	t_tmpliste	*cur;

	cur = *begin_list;
	if (cur == NULL)
		return ;
	while (cur->next != NULL )
	{
		if ((cur)->quotes == -1 && (cur)->next->quotes == -1)
			ft_deletenode(begin_list, cur);
		cur = cur->next;
	}
}

int	lstsize(t_tmpliste *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
