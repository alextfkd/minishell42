/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bultin_cmd_in_parent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/28 03:31:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_saved_stdio_fds(int saved_fd[2])
{
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	saved_fd[0] = dup(STDIN_FILENO);
	if (saved_fd[0] == -1)
	{
		perror("minishell: dup failed for STDIN");
		return (1);
	}
	saved_fd[1] = dup(STDOUT_FILENO);
	if (saved_fd[1] == -1)
	{
		perror("minishell: dup failed for STDOUT");
		close(saved_fd[0]);
		return (1);
	}
	return (0);
}

static void	_restore_fd_and_close(int saved_fd[2])
{
	if (dup2(saved_fd[0], STDIN_FILENO) == -1)
		perror("minishell: restore stdin failed");
	if (dup2(saved_fd[1], STDOUT_FILENO) == -1)
		perror("minishell: restore stdout failed");
	close(saved_fd[0]);
	close(saved_fd[1]);
}

// execute only one bultin cmd in parente process.
// if there is redirection,execute that as well.
int	exec_builtin_cmd_in_parent(t_list *p, char **envp)
{
	t_cmd			*cmd;
	t_builtin_type	type;
	int				saved_fd[2];
	int				status;

	status = -1;
	cmd = (t_cmd *)p->content;
	type = get_builtin_type(cmd);
	if (type != BT_NOT_BULTIN && type <= BT_EXIT && BUILTIN_ON)
	{
		status = 0;
		if (_saved_stdio_fds(saved_fd))
			return (1);
		if (status == 0)
		{
			log_debug("execute only one builtin command in parent process",
				LOG_DEBUG);
			status = exec_bulitin_cmd(cmd, envp);
		}
		_restore_fd_and_close(saved_fd);
		return (status);
	}
	return (status);
}
