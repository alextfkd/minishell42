/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:26:06 by marvin            #+#    #+#             */
/*   Updated: 2025/11/12 13:54:25 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# ifndef LOGLEVEL
#  define LOGLEVEL LOG_QUIET
# endif
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 700

# include "exec.h"
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
# include <limits.h>
# define FT_PROMPT "minishell$ "

extern volatile sig_atomic_t	g_sig_received;

typedef enum e_loglevel
{
	LOG_DEBUG = 0,
	LOG_WARNING = 1,
	LOG_INFO = 2,
	LOG_QUIET = 3,
}								t_loglevel;

typedef struct s_ms_buf
{
	char						*rl_buf;
	char						*tmp_buf;
	char						*sh_buf;
}								t_ms_buf;

typedef enum e_shell_status
{
	SHELL_SUCCESS = 0,
}								t_status;

typedef struct s_shell
{
	int							argc;
	char						**argv;
	t_ms_buf					*ms_buf;
	t_loglevel					loglevel;
	t_status					status;
}								t_shell;

int			interactive_shell(t_shell *shell, char **envp);
int			non_interactive_shell(t_shell *shell, char **envp);

void		log_debug(char *msg, t_loglevel log_level);
void		log_debug_show_input(char *msg,
				t_loglevel log_level);
void		log_warning(char *msg, t_loglevel log_level);
void		log_info(char *msg, t_loglevel log_level);
void		log_debug_show_token(t_token *token_head, t_loglevel log_level);
void		log_debug_show_ast(t_astree *ast_root, t_loglevel log_level);
void		print_redirections(t_red *red);
void		sigint_handler(int signal);
int			exit_with_sigeof(void);

t_ms_buf	*create_ms_buf(void);
void		log_debug_ms_buf(t_shell *shell);

void		free_ms_buf(t_ms_buf *ms_buf);
void		free_tmp_buf(t_ms_buf *ms_buf);
void		free_shell_buf(t_ms_buf *ms_buf);
void		free_readline_buf(t_ms_buf *ms_buf);

int			execute_cmd(char *inpt, char **envp, t_loglevel log_level);
void		exec_line(t_shell *shell, char **envp);
t_shell		*create_t_shell(int argc, char **argv);
t_status	free_t_shell(t_shell *shell);
int			set_cmd_redirection(t_cmd *cmd, t_token **current);

// app utils
int			free_app(t_app *app);
int			setup_app(t_app *app, char **envp);
void		reset_stdio(t_app *app);

// env utils
t_env		*envp_to_env_list(char **envp);
char		**env_list_to_envp(t_env *env_list);
char		**update_envp(t_env *env_list, char **current_envp);
void		free_envp(char **envp, size_t size);
char		*get_key_env_line(const char *envp_line);
char		*get_value_env_line(const char *envp_line);
char		**dup_envp(char **main_envp);
char		*env_get_value(t_env *env_list, const char *key);

//env list util
void		free_env_list(t_env *env_list);
t_env		*env_new_node(const char *envp_line);
size_t		env_list_size(t_env *env_list);
void		env_list_add_back(t_env **env_list, t_env *new_node);
t_env		*env_last_list(t_env *env_list);
t_astree	*astree_create_cmd_node(t_token **tokens_head);
t_astree	*astree_create_pipe_node(t_astree *left, t_astree *right);

#endif
