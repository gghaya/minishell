/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:40:47 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/02 19:04:22 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <string.h>
# include "ft_libft/libft.h"
# include <stdbool.h>


extern int g_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	// int				position;
	// int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	int						token;
	char					*file;
	struct s_redirection	*next;
}	t_redirect;

// typedef struct s_red
// {
// 	char					*token;
// 	int						flag;
// 	char					*file;
// 	int						fquotes;
// 	struct s_red			*next;
// }	t_red;

typedef struct s_tmpliste
{
	char						*arg;
	int							quotes;
	int							fd;
	struct s_tmpliste			*next;
}	t_tmpliste;

typedef struct s_finalstruct
{
	char					**cmd;
	t_redirect				*rdct;
	struct s_finalstruct	*next;
}	t_final;

bool		balanced_quotes(char *str);
t_tmpliste	*ft_splt(char *s);
t_tmpliste	*ft_lstnw(char *content, int quotes);
void		ft_lstad_back(t_tmpliste **lst, t_tmpliste *new);
void		ft_print(t_tmpliste *t);
void		ft_spacepipe(t_tmpliste **head, char *s, int *i);
void		ft_quotes(t_tmpliste **head, char *s, int *i);
void		ft_string(t_tmpliste **head, char *s, int *i);
void		ft_stclear(t_tmpliste **lst, void (*del)(void*));
void		ft_deletenode(t_tmpliste **begin_list, t_tmpliste *node);
void		ft_deletespace(t_tmpliste **begin_list);
bool		ft_help(t_tmpliste *liste, t_env *envp);
int			not_in(char *string, char c);
void		ft_redirection(t_tmpliste **begin_list, int k);
t_tmpliste	*add_node(t_tmpliste *prev, char *content);
char		*ft_check_cmd(char *arg, int	*i);
t_tmpliste	*ft_check_redirect(char *arg, t_tmpliste	*redirect,
				int	*i, int k);
t_tmpliste	*ft_red1(char	*arg, int	*i,  t_tmpliste	*red, int k);
int			lstsize(t_tmpliste *lst);
int			is_token(char *string);
bool		syntax_error(t_tmpliste *tmp);
int			ft_strcmp(char *s1, char *s2);
void		delete_empty(t_tmpliste **tmp);
int			sstrlen(const char *s);
bool		help_syntax(t_tmpliste *cur, t_tmpliste *tmp);
void		ft_heredoc(t_tmpliste **tmp, t_env	*env);
void		deletesp(t_tmpliste **tmp);
int			ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env);
t_env		*ft_envnw(char *key);
void		ft_add_env(t_env **lst, t_env *new);
t_env		*fill_env(char	**envp);
void		ft_expanding(t_tmpliste **tmp, t_env	*env);
// char		*expand(char	*arg, t_env	*env);
char		*fill_arg(char	*arg, char	**substring, int *len, int klen);
char		*getenv_(char	*key, t_env *env);
int			is_id(char c);
void		ft_envclear(t_env **lst, void (*del)(void*));
int			*without_dollar(char	*s);
// char		*is_exitstatus(char *arg);
int			nw_lenght(char*	arg, t_env	*env);
char	*expandd(char	*s, t_env *env);
#endif