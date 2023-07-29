/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:17:30 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 18:23:11 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fix_redirection(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_red	*fl;
	t_red	*cur_red;
	cur = (*tmp);
	printf("______\n");
	while (cur)
	{
		cur_red = cur->redirect;
		if (cur->redirect != NULL)
		{
			printf("1**\n");
			while (cur_red->next != NULL)
				cur_red = cur_red->next;
			fl = cur_red;
			printf("2**\n");
			if (ft_strcmp(cur_red->file, "") == 0)
			{
				printf("**\n");
				printf("**\n");
				cur = cur->next;
				if (cur != NULL && cur->quotes == -1)
					cur = cur->next;
				if (!cur)
					return ;
				else if (cur != NULL && cur->quotes != -2)
				{
					printf("**\n");
					fl->file = cur->arg;
					fl->fquotes = cur->quotes;
					cur->arg = "";
					printf("**\n");
				}
				cur = cur->next;
			}
			else
				cur = cur->next;
			printf("3**\n");
		}
		else
			cur = cur->next;
	}
	printf("______\n");
}

void	delete_empty(t_tmpliste **tmp)
{
	t_tmpliste	*cur;

	cur = (*tmp);
	while (cur)
	{
		if (ft_strcmp(cur->arg, "") == 0 && (cur->redirect == NULL
				|| ft_strcmp(cur->redirect->token, "") == 0))
		{
			ft_deletenode(tmp, cur);
		}
		cur = cur->next;
	}
}