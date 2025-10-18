/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:23:05 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 17:19:17 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "exec.h"

// create child process
static void	_child_process(char *cmd_path, char **av, char **ep)
{
	if (execve(cmd_path, av, ep) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		if (errno == EACCES)
			exit(126);
		else
			exit(CMD_NOT_FOUND);
	}
}

// wait child process
static int	_wait_for_child_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid failed");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

// execute shell command
int	exec_shell_cmd(t_cmd *cmd, char **ep)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_cmd_path(cmd->av[0]);
	if (!cmd_path)
	{
		printf("minishell: command not found: %s\n", cmd->av[0]);
		return (CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork failed");
		free(cmd_path);
		return (1);
	}
	else if (pid == 0)
	{
		_child_process(cmd_path, cmd->av, ep);
	}
	free(cmd_path);
	status = _wait_for_child_process(pid);
	return (status);
}
