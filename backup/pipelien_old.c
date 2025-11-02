/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelien_old.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 04:27:06 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_execve_exit_error(void)
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static int	_execute_builtin_child(t_cmd *cmd, t_app *app)
{
	int	status;

	status = execute_builtin_cmd(cmd, app);
	return (status);
}

static void	_execute_single_cmd(t_cmd *cmd, t_app *app)
{
	char	*cmd_path;

	if (handle_redirections(cmd->red, app) != 0)
		exit(1);
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
		exit(_execute_builtin_child(cmd, app));
	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		printf("minshell: %s :command not found \n", cmd->argv[0]);
		exit(127);
	}
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		_execve_exit_error();
	}
}

static int	_set_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

// execute pipe process
// The AST pipe node (NODE_PIPE) receives input
// and coordinates multiple commands.
int	execute_pipeline(t_astree *node, t_app *app)
{
	int		pipe_fds[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;

	if (node == NULL)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd_node(node->cmd, app));
	if (node->type == NODE_PIPE)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("minishell: pipe");
			return (1);
		}
		pid_left = fork();
		if (pid_left == -1)
		{
			perror("minishell: fork");
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			return (1);
		}
		if (pid_left == 0)
		{
			dup2(pipe_fds[1], STDOUT_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			if (node->left->type == NODE_CMD)
				_execute_single_cmd(node->left->cmd, app);
			else
				exit(execute_pipeline(node->left, app));
		}
		pid_right = fork();
		if (pid_right == -1)
		{
			perror("minishell: fork");
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			return (1);
		}
		if (pid_right == 0)
		{
			dup2(pipe_fds[0], STDIN_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			if (node->right->type == NODE_CMD)
				_execute_single_cmd(node->right->cmd, app);
			else
				exit(execute_pipeline(node->right, app));
		}
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
		return (_set_exit_status(status));
	}
	return (0);
}
