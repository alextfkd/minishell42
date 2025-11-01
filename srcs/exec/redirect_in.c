/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/01 14:53:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_setup_in(t_red *red)
{
	int	fd;

	fd = open(red->file, O_RDONLY);
	if (fd == -1)
	{
		perror(red->file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	_setup_heredoc(t_red *red)
{
	int	fd;

	fd = open(red->file, O_RDONLY);
	if (fd == -1)
	{
		perror(red->file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	do_redirect_in(t_red *red)
{
	if (red->tk == TK_RED_IN)
		return (_setup_in(red));
	else if (red->tk == TK_RED_HEREDOC)
		return (_setup_heredoc(red));
	return (0);
}
