/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:02:54 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 11:58:20 by gghaya           ###   ########.fr       */
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
	list->redct = NULL;
	list->next = NULL;
	return (list);
}

t_env	*ft_envnw(char *key)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_tmpliste));
	if (!list)
		return (NULL);
	list->key = key;
	list->value = NULL;
	list->next = NULL;
	return (list);
}

void	ft_add_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

	i = 0;
	if (!str)
		return (0);
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
				printf("Minishell : unbalanced quotation \n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
