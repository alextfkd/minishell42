/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:26:06 by marvin            #+#    #+#             */
/*   Updated: 2025/10/20 06:18:52 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 700

# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>
# include <errno.h>
# include "libft.h"
# include "exec.h"
# define FT_PROMPT "> "

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

int			interactive_shell(int argc, char **argv, char **envp,
				t_loglevel log_level);
int			non_interactive_shell(
				int argc,
				char **argv,
				char **envp,
				t_loglevel log_level);

void		log_debug(char *msg, t_loglevel log_level);
void		log_debug_show_input(char *msg, t_loglevel log_level);
void		log_warning(char *msg, t_loglevel log_level);
void		log_info(char *msg, t_loglevel log_level);

void		sigint_handler(int signal);
int			exit_with_sigeof(void);

t_ms_buf	*create_ms_buf(void);
void		log_debug_ms_buf(t_ms_buf *ms_buf, t_loglevel log_level);

void		delete_ms_buf(t_ms_buf *ms_buf);
void		free_tmp_buf(t_ms_buf *ms_buf);
void		free_shell_buf(t_ms_buf *ms_buf);
void		free_readline_buf(t_ms_buf *ms_buf);

int			execute_cmd(char *input, char **envp, t_loglevel log_level);
void		exec_line(
				t_ms_buf *ms_buf,
				char **envp,
				t_loglevel log_level,
				int *status
				);

#endif
