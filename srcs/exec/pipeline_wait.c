/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:03:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/30 23:54:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ignores signals, waits for all child processes to terminate,
 *  and returns the final status.
 *
 * @param e
 * @param app
 * @return int
 */
int	wait_all_processes(t_exec *e, t_app *app)
{
	int	status;
	int	last_status;

	e->i = 0;
	last_status = 0;
	while (e->i < e->cmd_count)
	{
		if (waitpid(e->pids[e->i], &status, WUNTRACED) == -1)
			status = (1 << 8);
		if (e->i == e->cmd_count - 1)
			last_status = set_exit_status(status);
		e->i++;
	}
	if (app->shell)
		set_sigaction(app->shell);
	return (last_status);
}

void	execve_exit_error(void)
{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(127);
}

int	set_exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
	}
	else if (WIFSTOPPED(status))
	{
		exit_status = 128 + WSTOPSIG(status);
		ft_putstr_fd(" Stopped\n", 2);
	}
	else
		exit_status = 1;
	return (exit_status);
}
