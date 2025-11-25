/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 20:32:21 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_red *red, t_app *app)
{
	t_red	*current;
	int		status;

	current = red;
	status = 0;
	while (current != NULL)
	{
		if (current->tk == TK_RED_IN || current->tk == TK_RED_HEREDOC)
			status = do_redirect_in(current, app);
		else if (current->tk == TK_RED_OUT || current->tk == TK_RED_APPEND)
			status = do_redirect_out(current);
		if (status != 0)
			return (status);
		current = current->next;
	}
	return (0);
}
