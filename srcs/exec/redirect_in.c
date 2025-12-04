/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/04 23:05:30 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_setup_in(t_red *red, t_cmd *cmd)
{
	red->fd = open(red->file, O_RDONLY);
	if (red->fd == -1)
		return (print_cmd_error(cmd, red->file, strerror(errno), 0), 1);
	if (dup2(red->fd, STDIN_FILENO) == -1)
		return (perror("minishell: dup2 redirect in"), 1);
	close(red->fd);
	return (0);
}

static int	_setup_heredoc(t_red *red, t_app *app)
{
	int	status;

	status = handle_heredoc(red, app);
	if (status != 0)
		return (status);
	if (dup2(red->fd, STDIN_FILENO) == -1)
		return (perror("minishell: dup2 redirect here-doc"), 1);
	close(red->fd);
	free_tokens(app->token_head);
	return (0);
}

int	do_redirect_in(t_red *red, t_cmd *cmd, t_app *app)
{
	if (red->tk == TK_RED_IN)
		return (_setup_in(red, cmd));
	else if (red->tk == TK_RED_HEREDOC)
		return (_setup_heredoc(red, app));
	return (0);
}
