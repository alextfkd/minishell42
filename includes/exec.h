/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/19 22:43:03 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexer.h"

# define MAX_PID 100
# define MAX_ARGV 100
# define CMD_NOT_FOUND 127

typedef struct s_redirection	t_redirection;

// Auxiliary structure of redirection
typedef struct s_redirection
{
	t_tokenkind		tk;
	char			*file;
	t_redirection	*next;
}	t_redirection;

// Single command Structure
typedef struct s_cmd
{
	int				argc;
	char			**argv;
	t_redirection	*red;
}	t_cmd;

int		exec_pipeline(t_list *p, char **ep);
int		handle_fork_err(pid_t *pid);
int		handle_pipe_err(t_list *p, int *pipe_fds);
int		exec_single_cmd(t_cmd *cmd, char **ep);
char	*find_cmd_path(char *av0);
t_list	*parse_input(char *input);

#endif
