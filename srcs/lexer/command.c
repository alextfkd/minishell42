/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/01 12:09:51 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create new cmd node
static t_cmd	*_create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		perror("minishell: t_cmd memory allocated error");
		return (NULL);
	}
	return (cmd);
}

static int	_handle_red_or_cleanup(t_cmd *cmd, t_token **current_ptr)
{
	if (handle_red(cmd, current_ptr))
	{
		clear_cmd(cmd);
		return (1);
	}
	return (0);
}

static int	_parse_cmd_loop(t_cmd *cmd, t_token **current_ptr)
{
	t_token	*current;

	current = *current_ptr;
	while (current != NULL && current->tk != TK_PIPE)
	{
		if (is_red(current->tk))
		{
			if (_handle_red_or_cleanup(cmd, &current))
				return (1);
		}
		else
			current = current->next;
	}
	*current_ptr = current;
	return (0);
}

t_astree	*parse_command(t_token **tokens_head)
{
	t_cmd		*cmd;
	t_astree	*node;
	t_token		*current;
	t_token		*head;

	cmd = _create_cmd_node();
	head = *tokens_head;
	current = head;
	if (_parse_cmd_loop(cmd, &current))
		return (NULL);
	if (handle_argv(cmd, head, current))
	{
		clear_cmd(cmd);
		return (NULL);
	}
	*tokens_head = current;
	node = create_ast_node(NODE_CMD, cmd, NULL, NULL);
	return (node);
}
