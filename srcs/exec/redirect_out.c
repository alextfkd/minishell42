/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 03:40:40 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	_setup_out(t_red *red)
{
	red->fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (red->fd == -1)
	{
		perror(red->file);
		return (1);
	}
	if (dup2(red->fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: rediercti out");
		return (1);
	}
	close(red->fd);
	return (0);
}

static int	_setup_append(t_red *red)
{
	red->fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (red->fd == -1)
	{
		perror(red->file);
		return (1);
	}
	if (dup2(red->fd, STDOUT_FILENO) == -1)
	{
		perror("minishll: dup2 rediect append");
		return (1);
	}
	close(red->fd);
	return (0);
}

int	do_redirect_out(t_red *red)
{
	if (red->tk == TK_RED_OUT)
		return (_setup_out(red));
	else if (red->tk == TK_RED_APPEND)
		return (_setup_append(red));
	return (0);
}
