/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:03:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 11:25:03 by htsutsum         ###   ########.fr       */
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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	e->i = 0;
	last_status = 0;
	while (e->i < e->cmd_count)
	{
		if (waitpid(e->pids[e->i], &status, 0) == -1)
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
	else
		exit(127);
}

int	set_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
