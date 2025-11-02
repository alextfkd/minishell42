/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 04:16:51 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_execve_exit_error(void)
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static int	_set_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static void	_execute_child_process(t_cmd *cmd, t_app *app)
{
	char	*cmd_path;

	if (handle_redirections(cmd->red, app) != 0)
		exit(1);
	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		printf("minshell: %s :command not found \n", cmd->argv[0]);
		exit(127);
	}
	clear_residual_fds();
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		_execve_exit_error();
	}
}

int	execute_external_cmd(t_cmd *cmd, t_app *app)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		_execute_child_process(cmd, app);
	}
	else if (pid < 0)
	{
		perror("minishell:");
		return (1);
	}
	waitpid(pid, &status, 0);
	return (_set_exit_status(status));
}

int	execute_cmd_node(t_cmd *cmd, t_app *app)
{
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
	{
		app->exit_status = execute_builtin_parent(cmd, app);
		return (app->exit_status);
	}
	else
	{
		app->exit_status = execute_external_cmd(cmd, app);
		return (app->exit_status);
	}
}
