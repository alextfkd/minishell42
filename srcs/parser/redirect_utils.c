/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:44:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 13:59:14 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 1 if tk is 2 to 5.
int	is_red(t_tkind tk)
{
	return (tk == TK_RED_OUT || tk == TK_RED_APPEND || tk == TK_RED_IN
		|| tk == TK_RED_HEREDOC);
}

// Find the last redirection node. t_red is a singly linked list.
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

// Recursively free() redirection list.
void	clear_red(t_red **head_red)
{
	if (head_red == NULL || *head_red == NULL)
		return ;
	clear_red(&(*head_red)->next);
	if ((*head_red)->file != NULL)
	{
		free((*head_red)->file);
		(*head_red)->file = NULL;
	}
	free((*head_red));
	*head_red = NULL;
}
