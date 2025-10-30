/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/28 04:04:33 by htsutsum         ###   ########.fr       */
=======
/*   Updated: 2025/10/30 14:56:27 by htsutsum         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "lexer.h"
#include "minishell.h"

# define MAX_PID 100
# define MAX_ARGV 100
# define CMD_NOT_FOUND 127
# define BUILTIN_ON 0
# define HERE_DOC_PROMPT "> "
# define ERR_SYNTAX_TOKEN "minishell: syntax error near unexpected token"

typedef struct s_red	t_red;
typedef struct s_cmd	t_cmd;
typedef struct s_astree	t_astree;
typedef struct s_app	t_app;

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

// auxiliary structure of redirection
struct s_red
{
	t_tkind		tk;
	char		*data;
	t_red		*next;
};

// single command Structure
struct s_cmd
{
	int			argc;
	char		**argv;
	int			status;
	t_red		*red;
};

struct s_app
{
	char	**envp;
	int		exit_status;
	int		original_stdin;
	int		original_stdout;
};


int				exec_pipeline(t_list *p, char **ep);
int				handle_fork_err(pid_t *pid);
int				handle_pipe_err(t_list *p, int *pipe_fds);
int				exec_builtin_cmd_in_parent(t_list *p, char **envp);

t_builtin_type	get_builtin_type(t_cmd *cmd);
int				exec_single_cmd(t_cmd *cmd, char **ep);
int				exec_bulitin_cmd(t_cmd *cmd, char **envp);
char			*find_cmd_path(char *av0);


// simple test parser
t_list			*parse_input(char *input);
void			free_cmd_content(void *cmd_ptr);

// command parser
void		clear_cmd(t_cmd *cmd);
t_astree	*parse_command(t_token **tokens_head);

// perser
int 		is_red(t_tkind tk);
t_astree	*parse_pipeline(t_token **tokens_head);
int 		count_tk_char(t_token *start,t_token *end);

// redirection parser
void		clear_red(t_red *head_red);
t_red		*create_red_node(t_tkind tk, char *data);
int			handle_red(t_cmd *cmd, t_token **current);

// ast utils
t_astree	*create_ast_node(t_node type, t_cmd *cmd, t_astree *left, t_astree *right);
void		astree_add_branch(t_astree *root, t_astree *left, t_astree *right);
void		clear_astree(t_astree *node);

//execute
int		execute_pipeline(t_astree *node, t_app *app);

#endif
