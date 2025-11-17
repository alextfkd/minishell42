/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/16 13:07:23 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		_handle_pipe_execution(t_astree *node, t_app *app);
static pid_t	_execute_left_child(
					t_astree *left_node,
					t_app *app,
					int pipe_fds[2]);
static pid_t	_execute_right_child(
					t_astree *right_node,
					t_app *app,
					int pipe_fds[2]);
static int		_wait_for_pipeline(
					pid_t pid_left, pid_t pid_right, int pipe_fds[2]);

// execute pipe process
// The AST pipe node (NODE_PIPE) receives input
// and coordinates multiple commands.
int	execute_pipeline(t_astree *node, t_app *app)
{
	if (node == NULL)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd_node(node->cmd, app));
	if (node->type == NODE_PIPE)
		return (_handle_pipe_execution(node, app));
	return (0);
}

static int	_handle_pipe_execution(t_astree *node, t_app *app)
{
	int		pipe_fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	pid_left = _execute_left_child(node->left, app, pipe_fds);
	if (pid_left == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (1);
	}
	pid_right = _execute_right_child(node->right, app, pipe_fds);
	if (pid_right == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		waitpid(pid_left, NULL, 0);
		return (1);
	}
	return (_wait_for_pipeline(pid_left, pid_right, pipe_fds));
}

static pid_t	_execute_left_child(
		t_astree *left_node,
		t_app *app,
		int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	else if (pid == 0)
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		if (left_node->type == NODE_CMD)
			execute_single_cmd(left_node->cmd, app);
		else
			exit(execute_pipeline(left_node, app));
	}
	return (pid);
}

static pid_t	_execute_right_child(
		t_astree *right_node,
		t_app *app,
		int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	else if (pid == 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		if (right_node->type == NODE_CMD)
			execute_single_cmd(right_node->cmd, app);
		else
			exit(execute_pipeline(right_node, app));
	}
	return (pid);
}

static int	_wait_for_pipeline(pid_t pid_left, pid_t pid_right, int pipe_fds[2])
{
	int	status;

	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (waitpid(pid_left, NULL, 0) == -1)
	{
		perror("minishell: pid_left waitpid");
		return (1);
	}
	if (waitpid(pid_right, &status, 0) == -1)
	{
		perror("minishell: pid_right waitpid");
		return (1);
	}
	return (set_exit_status(status));
}
