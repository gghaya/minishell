/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:02:54 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 18:11:27 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tmpliste	*ft_lstnw(char *content, int quotes)
{
	t_tmpliste	*list;

	list = (t_tmpliste *)malloc(sizeof(t_tmpliste));
	if (!list)
		return (NULL);
	list->arg = content;
	list->quotes = quotes;
	list->fd = -1;
	list->next = NULL;
	list->redirect = NULL;
	return (list);
}

t_red	*ft_rednw(char *token)
{
	t_red	*list;

	list = (t_red *)malloc(sizeof(t_red));
	if (!list)
		return (NULL);
	list->token = token;
	list->file = NULL;
	list->next = NULL;
	list->flag = -1;
	list->fquotes = 0;
	return (list);
}

void	ft_red_back(t_red **lst, t_red *new)
{
	t_red	*tmp;

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

void	ft_lstad_back(t_tmpliste **lst, t_tmpliste *new)
{
	t_tmpliste	*tmp;

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

bool	balanced_quotes(char *str)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			s = ft_strchr(str + i + 1, str[i]);
			if (s != NULL)
			{
				str = s;
				i = 0;
			}
			else
			{
				printf("error\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
