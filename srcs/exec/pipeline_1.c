/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 04:27:08 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execve_exit_error(void)
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static int	_execute_builtin_child(t_cmd *cmd, t_app *app)
{
	int	status;

	status = execute_builtin_cmd(cmd, app);
	return (status);
}

void	execute_single_cmd(t_cmd *cmd, t_app *app)
{
	char	*cmd_path;

	if (handle_redirections(cmd->red, app) != 0)
		exit(1);
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
		exit(_execute_builtin_child(cmd, app));
	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		printf("minshell: %s :command not found \n", cmd->argv[0]);
		exit(127);
	}
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		_execve_exit_error();
	}
}

int	set_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
