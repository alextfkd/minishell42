/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/12 00:40:26 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexer.h"
# include "libft.h"

# define MAX_FD 1024
# define MAX_PID 100
# define MAX_ARGV 100
# define BUILTIN_ON 0
# define HERE_DOC_PROMPT "> "
# define ERR_SYNTAX_TOKEN "minishell: syntax error near unexpected token"

// auxiliary structure of redirection (Singly linked list).
typedef struct s_red	t_red;
typedef struct s_cmd	t_cmd;
typedef struct s_astree	t_astree;
typedef struct s_app	t_app;
typedef struct s_env	t_env;

// type of a bulitin command
typedef enum e_bultin_type
{
	BT_NOT_BULTIN = 0,
	BT_CD,
	BT_EXPORT,
	BT_UNSET,
	BT_EXIT,
	BT_ECHO,
	BT_PWD,
	BT_ENV
}	t_builtin_type;

// AST node
typedef enum e_node
{
	NODE_CMD,
	NODE_PIPE
}	t_node;

// AST
struct	s_astree
{
	t_node		type;
	t_cmd		*cmd;
	t_astree	*left;
	t_astree	*right;
};

struct	s_red
{
	t_tkind	tk;
	int		fd;
	char	*file;
	t_red	*next;
};

// single command Structure
struct	s_cmd
{
	int		argc;
	char	**argv;
	t_red	*red;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct	s_app
{
	char	**envp;
	t_env	*env_list;
	int		exit_status;
	int		original_stdin;
	int		original_stdout;
};

void			clear_cmd(t_cmd *cmd);
int				set_cmd_argv(t_cmd *cmd, t_token *start, t_token *end);
t_cmd			*tokens2cmd(t_token **tokens_head);

// pipeline perser
t_astree		*parse_pipeline(t_token **tokens_head);

int				is_red(t_tkind tk);
void			clear_red(t_red *head_red);
void			red_add_back(t_red **head_red, t_red *new);
int				append_red_to_cmd(t_cmd *cmd, t_token *current);

void			astree_add_branch(t_astree *root, t_astree *left,
					t_astree *right);
void			astree_clear(t_astree *node);

// execute
t_builtin_type	get_builtin_type(t_cmd *cmd);
int				execute_cmd_node(t_cmd *cmd, t_app *app);
int				execute_pipeline(t_astree *node, t_app *app);
int				execute_builtin_cmd(t_cmd *cmd, t_app *app);
int				execute_builtin_parent(t_cmd *cmd, t_app *app);
char			*find_cmd_path(char *av0);
void			set_heredoc_signals(void);
int				handle_heredoc(t_red *red, t_app *app);
int				do_redirect_in(t_red *red, t_app *app);
int				do_redirect_out(t_red *red);
int				handle_redirections(t_red *red, t_app *app);
int				set_exit_status(int status);
void			execute_single_cmd(t_cmd *cmd, t_app *app);
void			clear_residual_fds(void);

t_cmd	*tokens2cmd(t_token **tokens_head);
void	clear_cmd(t_cmd *cmd);

int		set_cmd_redirection(t_cmd *cmd, t_token **current);

int		is_red(t_tkind tk);
t_red	*find_last_red(t_red *red);
void	red_add_back(t_red **head_red, t_red *new);
void	clear_red(t_red *head_red);

int		set_cmd_argv(t_cmd *cmd, t_token *start, t_token *end);
#endif
