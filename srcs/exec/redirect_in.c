/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 03:41:57 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_setup_in(t_red *red)
{
	red->fd = open(red->file, O_RDONLY);
	if (red->fd == -1)
	{
		perror(red->file);
		return (1);
	}
	if (dup2(red->fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 redirect in");
		return (1);
	}
	close(red->fd);
	return (0);
}

static int	_setup_heredoc(t_red *red, t_app *app)
{
	if (handle_heredoc(red, app))
		return (1);
	if (dup2(red->fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 redirect here-doc");
		return (1);
	}
	close(red->fd);
	return (0);
}

int	do_redirect_in(t_red *red, t_app *app)
{
	if (red->tk == TK_RED_IN)
		return (_setup_in(red));
	else if (red->tk == TK_RED_HEREDOC)
		return (_setup_heredoc(red, app));
	return (0);
}
