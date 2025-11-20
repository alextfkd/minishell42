/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/20 19:34:39 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_heredoc_line(char *line, t_app *app)
{
	(void)app;
	return (line);
}

static void	_print_heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("\')", 2);
}

static void	_heredoc_routine(char *delimiter, int *pipe_fds,int do_expand, t_app *app)
{
	char	*line;

	while (1)
	{
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
		if(do_expand)
			line = expand_heredoc_line(line, app);
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
}

static void _heredoc_child(char *delimiter, int *pipe_fds, int quote_flag, t_app *app)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);

	if (app->original_stdout != -1)
	{
		if (dup2(app->original_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			exit(1);
		}
	}
	close(pipe_fds[0]);
	//: !quote_flag と app の改善が必要になる。
	_heredoc_routine(delimiter, pipe_fds, !quote_flag, app);
	close(pipe_fds[1]);
	exit(0);
}

static int  _wait_for_heredoc(pid_t pid, int pipe_fds[2], t_app *app)
{
	int status;

	(void)app;
	close(pipe_fds[1]);
	signal(SIGINT, SIG_IGN);

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		perror("minishell: heredoc waitpid");
		close(pipe_fds[0]);
		return (1);
	}
	if(app->shell)
		set_sigaction(app->shell);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fds[0]);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}

int handle_heredoc(t_red *red, t_app *app)
{
	int	pid;
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("heredoc pipe error");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		perror("minishell: heredoc fork error");
		return (1);
	}
	if (pid == 0)
		_heredoc_child(red->file, pipe_fds, red->is_quoted, app);

	if (_wait_for_heredoc(pid, pipe_fds, app) == 0)
	{
		red->fd = pipe_fds[0];
		return (0);
	}
	else
	{
		return (1);
	}
}
