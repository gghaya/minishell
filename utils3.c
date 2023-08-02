/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:20:33 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/01 20:09:41 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_tmpliste **begin_list, int k)
{
	t_tmpliste	*cur;
	int			i;
	char		*tmp;

	cur = *begin_list;
	i = 0;
	while (cur)
	{
		if (cur->quotes == 0)
		{
			tmp = cur->arg;
			cur->arg = ft_check_cmd(tmp, &i);
			cur = ft_check_redirect(tmp, cur, &i, k);
			free(tmp);
			i = 0;
		}
		cur = cur->next;
	}
	free(cur);
}

bool	ft_help(t_tmpliste *liste, char	**envp)
{
	char	*input;
	int		k;
	t_env	*env_struct;
	// (void)envp;
	k = 0;
	input = readline("Minishell> ");
	if (!input)
		exit(1);
	add_history(input);
	if (balanced_quotes(input))
	{
		liste = ft_splt(input);
		free(input);
		ft_deletespace(&liste);
		ft_redirection(&liste, k);
		delete_empty(&liste);
		if (syntax_error(liste) == 0)
			return (ft_stclear(&liste, free), 0);
		else
		{
			ft_heredoc(&liste);
			deletesp(&liste);
			env_struct = fill_env(envp);
			// // free(env_struct);
			ft_expanding(&liste, env_struct);
			// // // system("leaks minishell");
			ft_envclear(&env_struct, free);
			ft_print(liste);
		}
		ft_stclear(&liste, free);
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

t_env	*fill_env(char	**envp)
{
	t_env	*env;
	t_env	*begin_env;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	begin_env = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env = ft_envnw(ft_substr(envp[i], 0, j));
		start = ++j;
		while (envp[i][j] && envp[i][j] != '\0')
			j++;
		env->value = ft_substr(envp[i], start, j - start);
		ft_add_env(&begin_env, env);
		i++;
	}
	// while ((begin_env))
	// {
	// 	printf ("key: <<%s>> ---->value:  <<%s>> \n", (begin_env)->key, (begin_env)->value);
	// 	(begin_env) = (begin_env)->next;
	// }
	return (begin_env);
}