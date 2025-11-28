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

static void	_setup_child_io(t_exec *e);
static void	_validate_cmd_redirection(t_cmd *cmd, t_app *app);
static void	_handle_cmd_not_found(char *cmd_name, t_app *app);

/**
 * @brief Pipe routing and built-in/external command assignment
 *
 * @param e
 * @param cmd
 * @param app
 */
void	child_routine(t_exec *e, t_cmd *cmd, t_app *app)
{
	int	exit_status;

	_setup_child_io(e);
	if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
	{
		exit_status = handle_redirections(cmd->red, app);
		if (exit_status != 0)
		{
			if (app && app->shell)
				free_shell(app->shell);
			exit(exit_status);
		}
		exit_status = execute_builtin_cmd(cmd, app);
		if (app && app->shell)
			free_shell(app->shell);
		exit(exit_status);
	}
	execute_external_cmd(cmd, app);
}

/**
 * @brief  Setup pipe file descriptors for child process
 *
 * @param e
 */
static void	_setup_child_io(t_exec *e)
{
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

	_validate_cmd_redirection(cmd, app);
	cmd_path = find_cmd_path(cmd->argv[0], app->env_list);
	if (!cmd_path)
		_handle_cmd_not_found(cmd->argv[0], app);
	close_unused_fds();
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		if (app && app->shell)
			free_shell(app->shell);
		execve_exit_error();
	}
}

/**
 * @brief Performs direct processing and checks for empty commands.
 *
 * @param cmd
 * @param app
 */
static void	_validate_cmd_redirection(t_cmd *cmd, t_app *app)
{
	int	ret;

	ret = handle_redirections(cmd->red, app);
	if (ret != 0)
	{
		if (app && app->shell)
			free_shell(app->shell);
		exit(ret);
	}
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
	{
		if (app && app->shell)
			free_shell(app->shell);
		exit(0);
	}
}

/**
 * @brief handle command not found error;
 *
 * @param cmd_name
 * @param app
 */
static void	_handle_cmd_not_found(char *cmd_name, t_app *app)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	if (app && app->shell)
		free_shell(app->shell);
	exit(127);
}
