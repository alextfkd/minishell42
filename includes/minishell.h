/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:26:06 by marvin            #+#    #+#             */
/*   Updated: 2025/11/24 22:06:39 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# ifndef LOGLEVEL
#  define LOGLEVEL LOG_QUIET
# endif
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 700

# include "types.h"
# include "exec.h"
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# define FT_PROMPT "minishell$ "

extern volatile sig_atomic_t	g_sig_received;

typedef enum e_loglevel
{
	LOG_DEBUG = 0,
	LOG_WARNING = 1,
	LOG_INFO = 2,
	LOG_QUIET = 3,
}	t_loglevel;

typedef struct s_ms_buf
{
	char	*rl_buf;
	char	*tmp_buf;
	char	*sh_buf;
}	t_ms_buf;

/*
typedef enum e_shell_status
{
	SHELL_SUCCESS = 0,
}								t_status;
*/

struct	s_shell
{
	int			argc;
	char		**argv;
	t_ms_buf	*ms_buf;
	t_loglevel	loglevel;
	int			status;
	t_app		*app;
};

int			interactive_shell(t_shell *shell);
int			non_interactive_shell(t_shell *shell);

void		log_debug(char *msg, t_loglevel log_level);
void		log_debug_show_input(char *msg, t_loglevel log_level);
void		log_warning(char *msg, t_loglevel log_level);
void		log_info(char *msg, t_loglevel log_level);
void		log_debug_show_token(t_token *token_head, t_loglevel log_level);
void		log_debug_show_ast(t_astree *ast_root, t_loglevel log_level);
void		print_redirections(t_red *red);

int			set_sigaction(t_shell *shell);
void		sigint_handler(int signal);
void		sigquit_handler(int signal);
int			exit_with_sigeof(void);

t_ms_buf	*create_ms_buf(void);
void		log_debug_ms_buf(t_shell *shell);

int			free_shell(t_shell *shell);
void		free_ms_buf(t_ms_buf *ms_buf);
void		free_tmp_buf(t_ms_buf *ms_buf);
void		free_shell_buf(t_ms_buf *ms_buf);
void		free_readline_buf(t_ms_buf *ms_buf);

char		*integrate_input_buffer(t_shell *shell);
int			execute_cmd(char *inpt, t_app *app, t_loglevel log_level);
void		exec_line(t_shell *shell);
t_shell		*create_t_shell(int argc, char **argv, char **envp);
int			free_t_shell(t_shell *shell);
int			set_cmd_redirection(t_cmd *cmd, t_token **current, int *status);
int			pipeline_executor(t_shell *shell);

// app utils
void		free_app(t_app *app);
t_app		*setup_app(char **envp, t_shell *shell);
void		reset_stdio(t_app *app);

// env utils
t_env		*envp_to_env_list(char **envp);
char		**env_list_to_envp(t_env *env_list);
char		**rebuild_envp(t_env *env_list, char **current_envp);
char		*get_key_env_line(const char *envp_line);
char		*get_value_env_line(const char *envp_line);
t_env		*get_env_from_env_line(const char *env_line);
char		**dup_env(char **main_envp);
char		*get_env_value(t_env *env_list, const char *key);
int			set_env_value(t_env **env_list, char *key, char *value);
void		update_underscore(t_app *app, t_cmd *cmd);

// env list util
void		free_env_list(t_env *env_list);
t_env		*env_new_node(char *key, char *value, int is_set);
size_t		env_list_size(t_env *env_list, int mode);
void		env_list_add_back(t_env **env_list, t_env *new_node);
t_env		*env_last_list(t_env *env_list);
t_astree	*astree_create_cmd_node(t_token **tokens_head, int *status);
t_astree	*astree_create_pipe_node(t_astree *left, t_astree *right,
				int *status);

int			parameter_expansion(t_app *app, t_astree *root);
char		*create_env_key_candidate(char *argv, int *status);
int			overwrite_argv(char **argv_i, char *new_argv);
int			trim_quotes(char **argv_i);
#endif
