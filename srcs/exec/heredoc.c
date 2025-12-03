/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/03 13:46:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_wait_for_heredoc(pid_t pid, int pipe_fds[2]);
static void	_heredoc_child(char *delimiter, int *pipe_fds, int is_quoted,
				t_app *app);
static void	_heredoc_routine(char *delimiter, int *pipe_fds, int is_quoted,
				t_app *app);
static char	*_process_expansion(char *line, int is_quoted, t_app *app);

int	handle_heredoc(t_red *red, t_app *app)
{
	int	pid;
	int	status;
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (perror("heredoc pipe error"), 1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (perror("minishell: heredoc fork error"), 1);
	}
	set_ignore_signal();
	if (pid == 0)
		_heredoc_child(red->file, pipe_fds, red->is_quoted, app);
	status = _wait_for_heredoc(pid, pipe_fds);
	if (status == 0)
	{
		red->fd = pipe_fds[0];
		return (0);
	}
	else
		return (status);
}

static void	_heredoc_child(
	char *delimiter,
	int *pipe_fds,
	int is_quoted,
	t_app *app)
{
	int	exit_status;

	signal(SIGINT, heredoc_exit_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	g_sig_received = 0;
	restore_heredoc_std_io(app, pipe_fds);
	close(pipe_fds[0]);
	close_heredoc_unused_fds(pipe_fds, app);
	_heredoc_routine(delimiter, pipe_fds, is_quoted, app);
	close(pipe_fds[1]);
	if (g_sig_received)
	{
		dup2(app->original_stdin, STDIN_FILENO);
		rl_deprep_terminal();
		ft_putendl_fd("^C", 2);
		exit_status = 130;
	}
	else
		exit_status = 0;
	free_shell_exit(app, exit_status);
}

/**
 * @brief Handles the main routine for reading input in a heredoc operation.
 * * This function continuously prompts the user for input, writes the lines
 * to a pipe, and stops when the delimiter is encountered or EOF is reached.
 *
 * @param delimiter
 * @param pipe_fds
 * @param do_expand A flag (1 or 0) indicating whether environment variable
 * @param app
 */
static void	_heredoc_routine(
	char *delimiter,
	int *pipe_fds,
	int is_quoted,
	t_app *app)
{
	char	*line;

	while (1)
	{
		line = readline(set_heredoc_prompt());
		if (!line)
		{
			if (g_sig_received)
				break ;
			print_heredoc_error(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = _process_expansion(line, is_quoted, app);
		if (!line)
			break ;
		ft_putendl_fd(line, pipe_fds[1]);
		free(line);
	}
}

static char	*_process_expansion(char *line, int is_quoted, t_app *app)
{
	char	*expanded;

	if (is_quoted)
		return (line);
	expanded = expand_heredoc_line(line, app);
	free(line);
	return (expanded);
}

static int	_wait_for_heredoc(pid_t pid, int pipe_fds[2])
{
	int	status;
	int	exit_status;

	close(pipe_fds[1]);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		close(pipe_fds[0]);
		return (perror("minishell: heredoc waitpid"), 1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_DFL);
	if (WIFSIGNALED(status))
		return (close(pipe_fds[0]), 128 + WTERMSIG(status));
	else if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			close(pipe_fds[0]);
		return (exit_status);
	}
	return (0);
}
