/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 20:00:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the types of bultin command.
t_builtin_type	get_builtin_type(t_cmd *cmd)
{
	const char	*name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	name = cmd->argv[0];
	if (ft_strcmp(name, "cd") == 0)
		return (BT_CD);
	if (ft_strcmp(name, "export") == 0)
		return (BT_EXPORT);
	if (ft_strcmp(name, "unset") == 0)
		return (BT_UNSET);
	if (ft_strcmp(name, "exit") == 0)
		return (BT_EXIT);
	if (ft_strcmp(name, "echo") == 0)
		return (BT_ECHO);
	if (ft_strcmp(name, "pwd") == 0)
		return (BT_PWD);
	if (ft_strcmp(name, "env") == 0)
		return (BT_ENV);
	return (BT_NOT_BULTIN);
}

// execute shell command
static void	_exec_shell_cmd(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		printf("minshell: %s :command not found \n", cmd->argv[0]);
		exit(127);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		perror("mnishell: ");
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
			exit(127);
	}
}

// execute bulti command
int	exec_bulitin_cmd(t_cmd *cmd, char **envp)
{
	(void)envp;
	printf("execute a builtin cmd -> %s\n", cmd->argv[0]);
	return (0);
}

// execute one shot cmd
int	exec_single_cmd(t_cmd *cmd, char **envp)
{
	int	status;

	status = 0;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
	{
		log_debug("execute a builtin command in child process", LOG_DEBUG);
		status = exec_bulitin_cmd(cmd, envp);
		return (status);
	}
	else
		_exec_shell_cmd(cmd, envp);
	return (status);
}
