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

/**
 * @brief Pipe routing and built-in/external command assignment
 *
 * @param e
 * @param cmd
 * @param app
 */
void	child_routine(t_exec *e, t_cmd *cmd, t_app *app)
{
	int	ret;

	if (e->prev_fd != STDIN_FILENO)
	{
		dup2(e->prev_fd, STDIN_FILENO);
		close(e->prev_fd);
	}
	if (e->current->next != NULL)
	{
		close(e->pipe_fds[0]);
		dup2(e->pipe_fds[1], STDOUT_FILENO);
		close(e->pipe_fds[1]);
	}
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
	{
		ret = handle_redirections(cmd->red, app);
		if (ret != 0)
			exit(ret);
		exit(execute_builtin_cmd(cmd, app));
	}
	execute_external_cmd(cmd, app);
}

/**
 * @brief Path Search and execve Execution (External Commands Only)
 *
 * @param cmd
 * @param app
 */
void	execute_external_cmd(t_cmd *cmd, t_app *app)
{
	char	*cmd_path;
	int		ret;

	ret = handle_redirections(cmd->red, app);
	if (ret != 0)
		exit(ret);
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		exit(0);
	cmd_path = find_cmd_path(cmd->argv[0], app->env_list);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	close_unused_fds();
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		execve_exit_error();
	}
}

/**
 * @brief Cleans up a pipeline execution by terminating and waiting
 *  for child processes,then freeing allocated memory.
 *
 * @param cmd_list
 * @param pids
 * @param count
 */
void	cleanup_pipeline(t_list *cmd_list, pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
	free_list(&cmd_list);
}

void	close_unused_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
	{
		close(fd);
		fd++;
	}
}
