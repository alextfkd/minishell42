/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 06:00:22 by htsutsum         ###   ########.fr       */
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

int	execute_builtin_cmd(t_cmd *cmd, t_app *app)
{
	(void)app;
	printf("execute a builtin cmd -> %s\n", cmd->argv[0]);
	return (0);
}

static void	_reset_std_fd(int tmp_stdin, int tmp_stdout)
{
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
	close(tmp_stdin);
	close(tmp_stdout);
}

int	execute_builtin_parent(t_cmd *cmd, t_app *app)
{
	int	status;
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDERR_FILENO);
	if (handle_redirections(cmd->red, app) != 0)
	{
		_reset_std_fd(tmp_stdin, tmp_stdout);
		return (1);
	}
	status = execute_builtin_cmd(cmd, app);
	_reset_std_fd(tmp_stdin, tmp_stdout);
	return (status);
}

void	clear_residual_fds(void)
{
	int	fd;
	int	max_fd;

	fd = 3;
	max_fd = MAX_FD;
	while (fd < max_fd)
	{
		close(fd);
		fd++;
	}
}
