/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/19 22:47:56 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean up file descriptors associated with the process
static void	_cleanup_parent_process(t_list **p, int *prev_fd_in, int *pipe_fds,
		int *i)
{
	if (*prev_fd_in != STDIN_FILENO)
		close(*prev_fd_in);
	if ((*p)->next != NULL)
	{
		close(pipe_fds[1]);
		*prev_fd_in = pipe_fds[0];
	}
	*p = (*p)->next;
	(*i)++;
}

// Create a childe process and execute the cmd
static void	_child_process(t_list *p, char **ep, int prev_fd_in, int *pipe_fds)
{
	int	status;

	status = 0;
	if (prev_fd_in != STDIN_FILENO)
	{
		if (dup2(prev_fd_in, STDIN_FILENO) == -1)
		{
			perror("minshell: dup2 STDIN failed");
			exit(1);
		}
		close(prev_fd_in);
	}
	if (p->next != NULL)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 STDOUT failed");
			exit(1);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	status = exec_single_cmd((t_cmd *)p->content, ep);
	exit(status);
}

// parente process wait for childe process
static int	_wait_for_child_process(pid_t *pid, int n)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	while (i < n)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("minishell: waitpid failed");
			return (1);
		}
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

// execute pipe process
int	exec_pipeline(t_list *p, char **envp)
{
	int		pipe_fds[2];
	int		prev_fd_in;
	pid_t	pid[MAX_PID];
	int		i;

	prev_fd_in = STDIN_FILENO;
	i = 0;
	while (p)
	{
		if (handle_pipe_err(p, pipe_fds) == -1)
			break ;
		if (handle_fork_err(&pid[i]) == -1)
			break ;
		if (pid[i] == 0)
			_child_process(p, envp, prev_fd_in, pipe_fds);
		else
			_cleanup_parent_process(&p, &prev_fd_in, pipe_fds, &i);
	}
	if (prev_fd_in != STDIN_FILENO)
		close(prev_fd_in);
	return (_wait_for_child_process(pid, i));
}
