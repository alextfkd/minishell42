/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/27 10:29:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check whether the command is a built-in command
static int	_is_builtin_cmd(t_cmd *cmd)
{
	int			i;
	const char	*b_cmd[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	i = 0;
	while (b_cmd[i] != NULL)
	{
		if (ft_strcmp(cmd->argv[0], b_cmd[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// execute shell command
static void	_exec_shell_cmd(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		printf("minshell: %s :command not found \n", cmd->argv[0]);
		exit(CMD_NOT_FOUND);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		perror("mnishell");
		free(cmd_path);
		exit(126);
	}
	if (execve(cmd_path, cmd->argv, envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		if (errno == EACCES)
			exit(126);
		else
			exit(CMD_NOT_FOUND);
	}
}

// execute bulti command
static	int	_exec_bulitin_cmd(t_cmd *cmd, char **envp)
{
	printf("exec builtin cmd : %s\n", cmd->argv[0]);
	return (0);
}

// execute one shot cmd
int	exec_single_cmd(t_cmd *cmd, char **envp)
{
	int	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (_is_builtin_cmd(cmd) && BUILTIN_ON)
	{
		status = _exec_bulitin_cmd(cmd,envp);
		return (status);
	}
	status = _exec_shell_cmd(cmd, envp);
	return (status);
}
