/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/03 17:55:12 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;
int	main(int ac, char **av, char **envp)
{
	t_tmpliste	*liste;
	t_env	*env_struct = fill_env(envp);

	liste = NULL;
	(void)ac;
	(void)av;
	// (void)envp;
	// (void)env_struct;
	// without_dollar("$HOME$");
	// is_exitstatus("$HOME$");
	while (1)
		ft_help(liste, env_struct);
	ft_envclear(&env_struct, free);
	// nw_lenght("$HOME", env_struct);
	return (0);
}

int	sstrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
1. if there is a token on its own -> syntax error
2. for only pipe: you should not start with a pipe
3. token followed by another token -> s.e. (except pipe followed by redirections)
4. token followed by '\0' ->s.e.
*/
/*
free empty nodes
*/ 

/*
is_identifier
1. Uppercase
2. Lowercase
3. Underscore
4. number
*/
/*
fix the addicionnaly space (ls << "")
syntaxe error <> ><
*/