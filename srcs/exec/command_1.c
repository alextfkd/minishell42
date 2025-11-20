/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 20:30:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_reset_std_fd(int tmp_stdin, int tmp_stdout);

int	execute_builtin_parent(t_cmd *cmd, t_app *app)
{
	int	status;
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	if (tmp_stdin == -1 || tmp_stdout == -1)
	{
		perror("minishell: dup");
		return (1);
	}
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

static void	_reset_std_fd(int tmp_stdin, int tmp_stdout)
{
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
	close(tmp_stdin);
	close(tmp_stdout);
}
