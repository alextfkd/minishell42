/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/03 22:53:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_run_builtin_process(t_exec e, t_app *app);
static int	_run_pipeline_loop(t_exec *e, t_app *app);
static int	_fork_and_exec(t_exec *e, t_app *app);
static void	_handle_parent_connection(t_exec *e);

int	execute_pipeline(t_astree *node, t_app *app)
{
	t_exec	e;
	int		status;
	t_cmd	*cmd;

	if (init_exec_vars(&e, node, app))
		return (1);
	cmd = (t_cmd *)e.cmd_list->content;
	if (e.cmd_count == 1 && get_builtin_type(cmd) != BT_NOT_BULTIN
		&& BUILTIN_ON)
		return (_run_builtin_process(e, app));
	e.pids = malloc(sizeof(pid_t) * e.cmd_count);
	if (!e.pids)
		return (free_pipeline_vars(&e, app), perror("malloc"), 1);
	set_ignore_signal();
	if (_run_pipeline_loop(&e, app) != 0)
		return (free_pipeline_vars(&e, app), 1);
	status = wait_all_processes(&e, app);
	update_underscore(app, (t_cmd *)ft_lstlast(e.cmd_list)->content);
	free_pipeline_vars(&e, app);
	return (status);
}

static int	_run_builtin_process(t_exec e, t_app *app)
{
	int		status;
	t_cmd	*cmd;

	status = execute_builtin_parent(e.cmd_list->content, app);
	cmd = (t_cmd *)e.cmd_list->content;
	if (status == -1)
		exit_process(0, app);
	update_underscore(app, cmd);
	free_pipeline_vars(&e, app);
	return (status);
}

/**
 * @brief Run the loop, perform pipe and fork operations,
 * and branch into parent and child processes.
 *
 * @param e
 * @param app
 * @return int
 */
static int	_run_pipeline_loop(t_exec *e, t_app *app)
{
	e->i = 0;
	e->prev_fd = STDIN_FILENO;
	e->current = e->cmd_list;
	while (e->current)
	{
		if (e->current->next && pipe(e->pipe_fds) == -1)
		{
			perror("minishell: pipe");
			if (e->prev_fd != STDIN_FILENO)
				close(e->prev_fd);
			cleanup_pipeline(e->cmd_list, e->pids, e->i);
			return (1);
		}
		if (_fork_and_exec(e, app) != 0)
			return (1);
		_handle_parent_connection(e);
		e->current = e->current->next;
		e->i++;
	}
	return (0);
}

/**
 * @brief Handles fork, child execution, and fork error management.
 */
static int	_fork_and_exec(t_exec *e, t_app *app)
{
	e->pids[e->i] = fork();
	if (e->pids[e->i] < 0)
	{
		perror("minishell: fork");
		if (e->current->next)
		{
			close(e->pipe_fds[0]);
			close(e->pipe_fds[1]);
		}
		if (e->prev_fd != STDIN_FILENO)
			close(e->prev_fd);
		cleanup_pipeline(e->cmd_list, e->pids, e->i);
		return (1);
	}
	if (e->pids[e->i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		free(e->pids);
		child_routine(e, (t_cmd *)e->current->content, app);
	}
	return (0);
}

/**
 * @brief Close the used pipe and update prev_fd
 *  for the next command.
 *
 * @param e
 */
static void	_handle_parent_connection(t_exec *e)
{
	if (e->prev_fd != STDIN_FILENO)
		close(e->prev_fd);
	if (e->current->next != NULL)
	{
		close(e->pipe_fds[1]);
		e->prev_fd = e->pipe_fds[0];
	}
	else
		e->prev_fd = STDIN_FILENO;
}
