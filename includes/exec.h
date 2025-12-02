/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/30 23:41:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "types.h"

# ifndef BUILTIN_ON
#  define BUILTIN_ON 1
# endif

# define MAX_FD 1024
# define ENV_SET 1
# define ENV_UNSET 0
# define ENV_ALL -1
# define FIRST_CHAR 1
# define OTHER_CHAR 0
# define PWD "PWD"
# define OLDPWD "OLDPWD"
# define HOME "HOME"
# define HERE_DOC_PROMPT "> "
# define ERR_SYNTAX_TOKEN_NL "syntax error near unexpected token `newline'"
# define ERR_SYNTAX_TOKEN_PIPE "syntax error near unexpected token `|'"
# define ERR_SYNTAX_TOKEN "minishell: syntax error near unexpected token"
# define ERR_UNMATCH_SQUOTE "unexpected EOF while looking for matching `''"
# define ERR_UNMATCH_DQUOTE "unexpected EOF while looking for matching `\"'"
# define ERR_UNEXPECTED_EOF "minishell: syntax error: unexpected end of file"

/*
typedef struct s_red			t_red;
typedef struct s_cmd			t_cmd;
typedef struct s_app			t_app;
typedef struct s_astree			t_astree;
typedef struct s_env			t_env;
typedef struct s_builtin_map	t_builtin_map;
typedef struct s_builtin_entry	t_builtin_entry;
typedef struct s_exec			t_exec;
typedef int						(*t_builtin_func)(t_app *app, t_cmd *s_cmd);

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

// auxiliary structure of redirection (Singly linked list).
struct	s_red
{
	t_tkind	tk;
	int		fd;
	int		is_quoted;
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
	int		is_set;
};

struct	s_app
{
	t_shell		*shell;
	char		**envp;
	t_env		*env_list;
	int			exit_status;
	int			original_stdin;
	int			original_stdout;
	t_astree	*astree_root;
	t_token		*token_head;
	t_list		*cmd_list;
};

struct	s_builtin_map
{
	const char		*name;
	t_builtin_type	type;
};

struct s_builtin_entry
{
	t_builtin_type	type;
	t_builtin_func	func;
};

struct s_exec
{
	t_list	*cmd_list;
	t_list	*current;
	pid_t	*pids;
	int		pipe_fds[2];
	int		prev_fd;
	int		cmd_count;
	int		i;
};
*/

// perser
t_astree			*create_astree_from_tokens(t_token **tokens_head,
						int *status);
int					append_red_to_cmd(t_cmd *cmd, t_token *current);
void				astree_add_branch(t_astree *root, t_astree *left,
						t_astree *right);
void				astree_clear(t_astree **node);
void				clear_cmd(t_cmd **cmd);
int					set_cmd_argv(t_cmd *cmd, t_token *start, t_token *end);
t_cmd				*tokens2cmd(t_token **tokens_head, int *status);
int					is_red(t_tkind tk);
t_red				*find_last_red(t_red *red);
void				red_add_back(t_red **head_red, t_red *new);
void				clear_red(t_red **head_red);

// execute builtin
t_builtin_type		get_builtin_type(t_cmd *cmd);
int					execute_builtin_parent(t_cmd *cmd, t_app *app);
int					execute_builtin_cmd(t_cmd *cmd, t_app *app);

// astree2list
t_list				*astree2list(t_astree *node);
void				free_list(t_list **list);

// execute pipline
int					execute_pipeline(t_astree *node, t_app *app);
void				execute_external_cmd(t_cmd *cmd, t_app *app);
void				update_underscore(t_app *app, t_cmd *cmd);
void				child_routine(t_exec *e, t_cmd *cmd, t_app *app);
void				cleanup_pipeline(t_list *cmd_list, pid_t *pids, int count);
void				close_unused_fds(void);
int					wait_all_processes(t_exec *e, t_app *app);
void				execve_exit_error(void);
int					set_exit_status(int status);
void				free_pipeline_vars(t_exec *e, t_app *app);
int					init_exec_vars(t_exec *e, t_astree *node, t_app *app);

// find cmd path
char				*find_cmd_path(char *av0, t_env *env_list);

// redirect
int					do_redirect_in(t_red *red, t_app *app);
int					do_redirect_out(t_red *red);
int					handle_redirections(t_red *red, t_app *app);

// heredoc
int					handle_heredoc(t_red *red, t_app *app);
char				*expand_line(char *line, t_app *app);
void				close_heredoc_unused_fds(int *pipe_fds, t_app *app);
void				restore_heredoc_std_io(t_app *app, int *pipe_fds);
void				print_heredoc_error(char *delimiter);
void				set_ignore_signal(void);

// builtin
int					ft_pwd(t_app *app, t_cmd *cmd);
int					ft_env(t_app *app, t_cmd *cmd);
int					ft_unset(t_app *app, t_cmd *cmd);
int					ft_export(t_app *app, t_cmd *cmd);
int					append_args_to_env_list(const char *args, t_env **env_list);
void				print_export_error(t_cmd *cmd, int i);
int					is_validate_args(const char *args);
int					is_env_char(char c, int mode);
int					append_args_to_env_list(const char *args, t_env **env_list);
int					print_env_attrib(const t_env *env_list);
int					ft_cd(t_app *app, t_cmd *cmd);
int					ft_echo(t_app *app, t_cmd *cmd);
int					ft_exit(t_app *app, t_cmd *cmd);
void				exit_process(int status, t_app *app);

#endif
