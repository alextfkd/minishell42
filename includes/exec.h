/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 02:39:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "types.h"

# ifndef BUILTIN_ON
#  define BUILTIN_ON 0
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
# define ERR_SYNTAX_TOKEN "minishell: syntax error near unexpected token"

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

// find cmd path
char				*find_cmd_path(char *av0, t_env *env_list);

// redirect
int					do_redirect_in(t_red *red, t_app *app);
int					do_redirect_out(t_red *red);
int					handle_redirections(t_red *red, t_app *app);

// heredoc
int					handle_heredoc(t_red *red, t_app *app);
char				*expand_heredoc_line(char *line, t_app *app);
void				close_heredoc_unused_fds(int *pipe_fds, t_app *app);
void				restore_heredoc_std_io(t_app *app, int *pipe_fds);
void				print_heredoc_error(char *delimiter);

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

#endif
