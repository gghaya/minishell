/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/04 20:15:54 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_tmpliste	*liste;
	t_env		*env_struct = fill_env(envp);

	liste = NULL;
	(void)ac;
	(void)av;
	// signal(SIGINT, c_handler);
	signal(SIGTERM, d_handler);
	while (1)
		ft_help(liste, env_struct);
	ft_envclear(&env_struct, free);
	return (0);
}

int	sstrlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
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

protection malloc
*/
// void	c_handler(int	signum)
// {
// 	(void)signum;
// 	return ;
// }

void	d_handler(int	signum)
{
	// (void)signum;

	if (signum == SIGTERM) {
        printf("Exit\n");
        exit(0); 
		}
}

// void	donothing_handler(int	signum)
// {
	
// }