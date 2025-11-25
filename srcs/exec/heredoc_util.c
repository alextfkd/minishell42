/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/24 19:56:39 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a warning when a heredoc is closed by EOF (Ctrl+D)
 *  instead of the delimiter.
 *
 * @param delimiter
 */
void	print_heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("\')", 2);
}

/**
 * @brief close unused fds.
 *
 * @param pipe_fds
 * @param app
 */
void	close_heredoc_unused_fds(int *pipe_fds, t_app *app)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
	{
		if (fd != pipe_fds[1]
			&& fd != app->original_stdin
			&& fd != app->original_stdout)
			close(fd);
		fd++;
	}
}

/**
 * @brief Restores the original stdin and stdout if they were saved.
 * Uses short-circuit evaluation to avoid nested ifs.
 * Exits with error if dup2 fails.
 *
 * @param app
 * @param pipe_fds
 */
void	restore_heredoc_std_io(t_app *app, int *pipe_fds)
{
	if ((app->original_stdin != -1
			&& dup2(app->original_stdin, STDIN_FILENO) == -1)
		|| (app->original_stdout != -1
			&& dup2(app->original_stdout, STDOUT_FILENO) == -1))
	{
		perror("minishell: dup2 stdio failed in heredoc");
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(1);
	}
}
