/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:44:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 06:36:29 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle redirection
int	handle_red(t_cmd *cmd, t_token **current)
{
	t_token	*operator;
	t_token	*file;
	t_red	*new_red;

	operator = *current;
	file = operator->next;
	if (file == NULL)
	{
		ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
		ft_putendl_fd("newline", 2);
		return (1);
	}
	if (file->tk != TK_CHAR)
	{
		ft_putendl_fd(ERR_SYNTAX_TOKEN, 2);
		return (1);
	}
	new_red = creaete_red_node(operator->tk, file->data);
	if (!new_red)
		return (1);
	red_add_back(&(cmd->red), new_red);
	*current == operator->next->next;
}

// create new redirection node
t_red	*create_red_node(t_tkind tk, char *data)
{
	t_red	*new;

	new = ft_calloc(sizeof(t_red), 1);
	if (!new)
	{
		perror("minishell: t_red memory allocated error");
		return (NULL);
	}
	new->tk = tk;
	new->data = data;
	new->next = NULL;
	return (new);
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
		head_red = new;
	else
		last_red = find_last_red(*head_red);
	last_red->next = new;
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
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
}
