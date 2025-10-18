/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:26:06 by marvin            #+#    #+#             */
/*   Updated: 2025/10/18 17:45:05 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

typedef enum e_loglevel
{
	LOG_DEBUG = 0,
	LOG_WARNING = 1,
	LOG_INFO = 2,
	LOG_QUIET = 3,
}	t_loglevel;

int		interactive_shell(int argc, char **argv, t_loglevel log_level);
int		non_interactive_shell(int argc, char **argv, t_loglevel log_level);

void	log_debug(char *msg, t_loglevel log_level);
void	log_debug_show_input(char *msg, t_loglevel log_level);
void	log_warning(char *msg, t_loglevel log_level);
void	log_info(char *msg, t_loglevel log_level);

void	sigint_handler(int signal);
int		exit_with_sigeof(void);

#endif
