/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:26:06 by marvin            #+#    #+#             */
/*   Updated: 2025/11/27 02:56:52 by htsutsum         ###   ########.fr       */
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
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "utils.h"
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

int			parameter_expansion(t_app *app, t_astree *root);
char		*create_env_key_candidate(char *argv, int *status);
int			overwrite_argv(char **argv_i, char *new_argv);
int			trim_quotes(char **argv_i);
#endif
