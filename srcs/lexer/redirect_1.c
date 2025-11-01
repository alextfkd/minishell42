/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:44:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 20:17:08 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(t_tkind tk)
{
	return (tk == TK_RED_OUT || tk == TK_RED_APPEND || tk == TK_RED_IN
		|| tk == TK_RED_HEREDOC);
}

// find the last redirection
t_red	*find_last_red(t_red *red)
{
	if (red)
		while (red->next)
			red = red->next;
	return (red);
}

// append new redirection
void	red_add_back(t_red **head_red, t_red *new)
{
	t_red	*last_red;

	if (!*head_red)
		*head_red = new;
	else
	{
		last_red = find_last_red(*head_red);
		last_red->next = new;
	}
}

// free redirection list
void	clear_red(t_red *head_red)
{
	t_red	*tmp;

	if (!head_red)
		return ;
	while (head_red != NULL)
	{
		tmp = head_red;
		head_red = head_red->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}
