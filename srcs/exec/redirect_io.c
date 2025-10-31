/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/01 00:24:09 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// >> >

int	handle_redirections(t_red *red_list)
{
	t_red	*current;
	int		status;

	current = red_list;
	status = 0;
	while (current != NULL)
	{
		if (current->tk == TK_RED_IN || current->tk == TK_RED_HEREDOC)
			status = do_redirect_in(current);
		else if (current->tk == TK_RED_OUT || current->tk == TK_RED_APPEND)
			status = do_redirect_out(current);
		if (status != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
