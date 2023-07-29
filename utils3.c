/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:20:33 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 12:10:31 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_tmpliste **begin_list)
{
	t_tmpliste	*cur;
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	cur = *begin_list;
	j = 0;
	while (cur)
	{
		if (cur->quotes == 0)
		{
			tmp = cur->arg;
			cur->arg = ft_check_cmd(tmp, &i);
			cur->redirect = ft_check_redirect(tmp, cur->redirect, &i); 
			free(tmp);
			j++;
			i = 0;
		}
		cur = cur->next;
	}
}

bool	ft_help(t_tmpliste *liste)
{
	char	*input;

	input = readline("Minishell> ");
	add_history(input);
	if (balanced_quotes(input))
	{
		liste = ft_splt(input);
		ft_deletespace(&liste);
		ft_redirection(&liste);
		if (syntax_error(liste) == 0)
			return (0);
		else
			ft_print(liste);
	}
	return (1);
}

int	not_in(char *string, char c)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_token(char *string)
{
		if (ft_strcmp(string, ">>") == 0 || ft_strcmp(string, "<<") == 0)
			return (1);
		else if (ft_strcmp(string, ">") == 0 || ft_strcmp(string, "<") == 0)
			return (1);
		return (0);
}

t_tmpliste	*add_node(t_tmpliste *prev, char *content)
{
	t_tmpliste	*node;
	t_tmpliste	*tmp;

	if (!prev)
		return (NULL);
	node = ft_lstnw(content, 0);
	tmp = prev->next;
	prev->next = node;
	node->next = tmp;
	return (node);
}

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

void ft_red1(char	*arg, int	*i, t_red	**red)
{
	int		k;
	t_red	*node;

	k = 0;
	if (arg[*i] == '>' || arg[*i] == '<')
	{
		(*i)++;
		if (arg[(*i)] && (arg[*i] == '>' || arg[*i] == '<'))
		{
			node = ft_rednw(ft_substr(arg, (*i) - 1, 2));
			k = ++(*i);
		}
		else
		{
			node = ft_rednw(ft_substr(arg, (*i) - 1, 1));
			k = (*i);
		}
		while (arg[(*i)] && not_in("|><", arg[(*i)]) == 0)
			(*i)++;
		node->file = ft_substr(arg, k, (*i) - k);
		ft_red_back(red, node);
	}
	else
		(*i)++;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}