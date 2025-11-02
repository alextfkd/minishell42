/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 22:04:40 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_exec_bulitin_cmd(t_cmd *cmd, t_app *app)
{
	(void)app;
	printf("execute a builtin cmd -> %s\n", cmd->argv[0]);
	return (0);
}

static void _reset_std_fd(int tmp_stdin, int tmp_stdout)
{
    dup2(tmp_stdin, STDIN_FILENO);
    dup2(tmp_stdout, STDOUT_FILENO);
    close(tmp_stdin);
    close(tmp_stdout);
}

static void _execve_exit_error()
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);

}
static int _set_exit_status(int status)
{
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int execute_external_command(t_cmd *cmd, t_app *app)
{
	int		status;
	pid_t	pid;
	char 	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(cmd->red) != 0)
			exit(1);
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
	else if(pid < 0)
	{
		perror("minishell:");
		return (1);
	}
	waitpid(pid, &status, 0);
	return(_set_exit_status(status));
}

int execute_builtin_parent(t_cmd *cmd, t_app *app)
{
	int status;
    int tmp_stdin;
    int tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDERR_FILENO);
    if (handle_redirections(cmd->red) != 0)
    {
        _reset_std_fd(tmp_stdin, tmp_stdout);
        return (1);
    }
    status = new_exec_bulitin_cmd(cmd, app);
    _reset_std_fd(tmp_stdin, tmp_stdout);
    return (status);
}

int execute_command_node(t_cmd *cmd, t_app *app)
{
    if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
    {
		app->exit_status = execute_builtin_parent(cmd,app);
        return (app->exit_status);
    }
    else
    {
		app->exit_status = execute_external_command(cmd,app);
        return (app->exit_status);
    }
}
