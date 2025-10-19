/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipline_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:41:13 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/19 22:46:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize forks and handle error
int	handle_fork_err(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork failed");
		return (-1);
	}
	return (0);
}

// Initialize pipe and handle error
int	handle_pipe_err(t_list *p, int *pipe_fds)
{
	if (p->next != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("minishell: pipe failed");
			return (-1);
		}
	}
	return (0);
}
