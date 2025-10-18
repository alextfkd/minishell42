/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:23:05 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 16:25:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "./libft/includes/libft.h"


// execute shell command
int	exec_shell_cmd(t_cmd *cmd, char **ep)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_cmd_path(cmd->av[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: command not found: %s\n", cmd->av[0]);
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
		if (execve(cmd_path, cmd->av, ep) == -1)
		{
			perror("minishell: execve failed");
			free(cmd_path);
			exit(CMD_NOT_FOUND);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		return (1);
	}
	return (0);
}
