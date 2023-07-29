/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:40:47 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/28 19:26:22 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include <readline/readline.h>
# include <string.h>
# include "ft_libft/libft.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				position;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	int						token;
	char					*file;
	struct s_redirection	*next;
}	t_redirect;

typedef struct s_red
{
	char					*token;
	int						flag;
	char					*file;
	struct s_red			*next;
}	t_red;

typedef struct s_tmpliste
{
	char						*arg;
	int							quotes;
	int							fd;
	struct s_red		*redirect;
	struct s_tmpliste			*next;
}	t_tmpliste;

typedef struct s_finalstruct
{
	char		**cmd;
	t_redirect	*rdct;
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
bool		ft_help(t_tmpliste *liste);
int			not_in(char *string, char c);
void		ft_redirection(t_tmpliste **begin_list);
t_tmpliste	*add_node(t_tmpliste *prev, char *content);
char		*ft_check_cmd(char *arg, int	*i);
t_red		*ft_check_redirect(char *arg, t_red	*redirect, int	*i);
t_red		*ft_rednw(char *token);
void		ft_red_back(t_red **lst, t_red *new);
void		ft_red1(char	*arg, int	*i, t_red	**red);
int			lstsize(t_tmpliste *lst);
int			is_token(char *string);
bool		handel_redirection(t_red *tmp_red);
bool		handel_redirection(t_red *tmp_red);
bool		syntax_error(t_tmpliste *tmp);
int			ft_strcmp(char *s1, char *s2);
#endif