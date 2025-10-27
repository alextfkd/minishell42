/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/27 18:17:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect_out(t_redirect *red)
{
	t_redirect	*current;
	int			fd;
	int			last_fd_opened;

	last_fd_opened = -1;
	current = red;
	while (current != NULL)
	{
		if (last_fd_opened != -1)
			close(last_fd_opened);
		if (current->tk == TK_REDI_OUT_TRUC)
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->tk == TK_REDI_OUT_APPEND)
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			current = current->next;
			continue ;
		}
		if (fd == -1)
		{
			perror("minishell: open error");
			return (1);
		}
		last_fd_opened = fd;
		current = current->next;
	}
	if (last_fd_opened != -1)
	{
		if (dup2(last_fd_opened, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error");
			close(last_fd_opened);
			return (1);
		}
		close(last_fd_opened);
	}
	return (0);
}
