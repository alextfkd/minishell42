/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/07 05:24:41 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_print_heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line", 1);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", 1);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("\')", 2);
}

static void	_heredoc_loop(char *delimiter, int *pipe_fds)
{
	char	*line;

	while (1)
	{
		fflush(stdout);
		line = readline(HERE_DOC_PROMPT);
		if (!line)
		{
			_print_heredoc_error(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
}

static int	_wait_for_heredoc(pid_t pid, int pipe_fds[2])
{
	int	status;

	close(pipe_fds[1]);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		perror("minishell: pid heredoc waitpid");
		return (1);
	}
	set_exit_status(status);
	return (0);
}

static void	_heredoc_child(char *delimiter, int *pipe_fds, t_app *app)
{
	(void)app;
	set_heredoc_signals();
	if (dup2(app->original_stdout, STDOUT_FILENO) == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(1);
	}
	close(pipe_fds[0]);
	_heredoc_loop(delimiter, pipe_fds);
	close(pipe_fds[1]);
	exit(0);
}

int	handle_heredoc(t_red *red, t_app *app)
{
	int		pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("heredoc pipe error");
		return (1);
	}
	red->fd = pipe_fds[0];
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		perror("minishell: heredoc pipe error");
		exit(1);
	}
	if (pid == 0)
		_heredoc_child(red->file, pipe_fds, app);
	return (_wait_for_heredoc(pid, pipe_fds));
}
