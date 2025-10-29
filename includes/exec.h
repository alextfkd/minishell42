/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/27 22:17:15 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexer.h"
# define MAX_PID 100
# define MAX_ARGV 100
# define CMD_NOT_FOUND 127
# define BUILTIN_ON 0
# define HERE_DOC_PROMPT "> "

typedef struct s_redirect	t_redirect;

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

// auxiliary structure of redirection
typedef struct s_redirect
{
	t_tokenkind		tk;
	char			*file;
	int				is_quated;
	t_redirect		*next;
}	t_redirect;

// single command Structure
typedef struct s_cmd
{
	int				argc;
	char			**argv;
	int				status;
	t_redirect		*red;
}	t_cmd;

int				exec_pipeline(t_list *p, char **ep);
int				handle_fork_err(pid_t *pid);
int				handle_pipe_err(t_list *p, int *pipe_fds);
int				exec_builtin_cmd_in_parent(t_list *p, char **envp);

t_builtin_type	get_builtin_type(t_cmd *cmd);
int				exec_single_cmd(t_cmd *cmd, char **ep);
int				exec_bulitin_cmd(t_cmd *cmd, char **envp);
char			*find_cmd_path(char *av0);

t_list			*parse_input(char *input);
void			free_cmd_content(void *cmd_ptr);

#endif
