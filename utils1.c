/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:02:54 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/28 19:28:47 by gghaya           ###   ########.fr       */
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
	return (list);
}

void	ft_red_back(t_red **lst, t_red *new)
{
	t_red	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		// new->next = NULL;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	// new->next = NULL;
}

void	ft_lstad_back(t_tmpliste **lst, t_tmpliste *new)
{
	t_tmpliste	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		// new->next = NULL;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	// new->next = NULL;
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

t_tmpliste	*ft_splt(char *s)
{
	int			i;
	t_tmpliste	*head;

	head = NULL;
	s = ft_strtrim(s, " \t");
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '|')
		{
			ft_spacepipe(&head, s, &i);
		}
		else if (s[i] == '\'' || s[i] == '\"')
		{
			ft_quotes(&head, s, &i);
		}
		else
		{
			ft_string(&head, s, &i);
		}
		i++;
	}
	free(s);
	return (head);
}

void	ft_print(t_tmpliste *t)
{
	while (t != NULL)
	{
		printf("command (%s) quote (%d)\n", t->arg, t->quotes);
		while(t->redirect != NULL)
		{
			printf("**redirection : (%s) file : (%s)\n", t->redirect->token , t->redirect->file);
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