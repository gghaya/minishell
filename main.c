/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 16:24:53 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env_struct;

	g_status = 0;
	// rl_catch_signals = 0;
 	(void)ac;
	(void)av;
	signal(SIGINT, &c_handler);
	signal(SIGQUIT, &quit_handler);
	env_struct = fill_env(envp);
	while (1)
	{
		input = readline("Minishell$ ");
		if (input == NULL)
		{
			// write (1, "exit\n", 5);
			printf("\033[11C");
			printf("\033[1A");
			printf("exit\n");
			exit(0);
		}
		ft_help(input, env_struct);
	}
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
void	c_handler(int signum)
{
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_handler(int signum)
{
	if (signum == SIGQUIT)
		return ;

}
