/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/31 17:30:26 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_tmpliste	*liste;

	liste = NULL;
	(void)ac;
	(void)av;
	// (void)envp;
	while (1)
		ft_help(liste, envp);
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