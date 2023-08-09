/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:40:47 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/09 11:09:04 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "ft_libft/libft.h"
# include <stdbool.h>
# include <signal.h>

# define IN	0
# define OUT	1
# define APPEND	2
# define HEREDOC	3

int	g_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	int						token;
	char					*file;
	struct s_redirection	*next;
}	t_redirect;

typedef struct s_tmpliste
{
	char						*arg;
	int							quotes;
	int							fd;
	struct s_redirection		*redct;
	struct s_tmpliste			*next;
}	t_tmpliste;

typedef struct s_finalstruct
{
	char					**cmd;
	struct s_redirection	*rdct;
	struct s_finalstruct	*next;
	int						fd;
}	t_final;

typedef struct s_ex
{
	int		len;
	int		i;
	int		j;
	int		start;
	int		x;
	char	*expnd;
	char	*res;
}	t_ex;

typedef struct s_strct
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;
	char		*str;
}	t_strct;

typedef struct s_s
{
	int		i;
	int		start;
	int		len;
	char	*s;
	char	*str;
}	t_s;

bool		balanced_quotes(char *str);
t_tmpliste	*ft_splt(char *s);
t_tmpliste	*ft_lstnw(char *content, int quotes);
void		ft_print(t_tmpliste *t);
void		ft_spacepipe(t_tmpliste **head, char *s, int *i);
void		ft_quotes(t_tmpliste **head, char *s, int *i);
void		ft_lstad_back(t_tmpliste **lst, t_tmpliste *new);
void		ft_string(t_tmpliste **head, char *s, int *i);
void		ft_stclear(t_tmpliste **lst, void (*del)(void*));
void		ft_deletenode(t_tmpliste **begin_list, t_tmpliste *node);
void		ft_deletespace(t_tmpliste **begin_list);
bool		ft_help(char	*input, t_env *envp);
int			not_in(char *string, char c);
void		ft_redirection(t_tmpliste **begin_list, int k);
t_tmpliste	*add_node(t_tmpliste *prev, char *content);
char		*ft_check_cmd(char *arg, int	*i);
t_tmpliste	*ft_check_redirect(char *arg, t_tmpliste	*redirect,
				int	*i, int k);
t_tmpliste	*ft_red1(char	*arg, int	*i, t_tmpliste	*red, int k);
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
char		*fill_arg(char	*arg, char	**substring, int *len, int klen);
char		*getenv_(char	*key, t_env *env);
int			is_id(char c);
void		ft_envclear(t_env **lst, void (*del)(void*));
int			*without_dollar(char	*s);
int			nw_lenght(char	*arg, t_env	*env);
char		*expandd(char	*s, t_env *env);
void		ft_join(t_tmpliste **tmp);
t_redirect	*ft_rednw(int token);
int			get_token(char	*s);
void		collect_red(t_tmpliste	**tmp);
t_tmpliste	*rm_node(t_tmpliste **begin_list, t_tmpliste *node);
t_tmpliste	*rm(t_tmpliste **begin_list, t_tmpliste *node);
t_final		*ft_help1(t_tmpliste *liste, t_env *env);
int			collect_help(t_tmpliste	**cur, char	*s);
int			red_error(t_tmpliste *tmp);
t_redirect	*copy_red(int token, char	*file);
t_final		*new_final(int len);
void		add_final_back(t_final **lst, t_final *new);
void		ft_redct_back(t_redirect **lst, t_redirect *new);
t_tmpliste	*help_final(t_final	**fhead, t_tmpliste	*cur, int len);
int			cmd_len(t_tmpliste	*prev);
t_final		*fill_final(t_tmpliste **tmp);
void		show_final(t_final	*f);
void		quit_handler(int signum);
void		c_handler(int signum);
int			do_1(t_s *s);
int			do_2(t_s *s, char	*arg, t_env *env);
int			expand_2(t_ex	*ex, char	*s, t_env	*env);
int			expand_1(t_ex	*ex);
#endif