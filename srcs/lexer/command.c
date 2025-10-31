/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 16:38:14 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create new cmd node
t_cmd	*_create_cmd_node(void)
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

t_astree	*parse_command(t_token **tokens_head)
{
	t_cmd		*cmd;
	t_astree	*node;
	t_token		*current;
	t_token		*head;

	cmd = _create_cmd_node();
	head = *tokens_head;
	current = head;
	while (current != NULL && current->tk != TK_PIPE)
	{
		if (is_red(current->tk))
		{
			if (handle_red(cmd, &current))
			{
				clear_cmd(cmd);
				return (NULL);
			}
		}
		else
			current = current->next;
	}
	if (handle_argv(cmd, head, current))
	{
		clear_cmd(cmd);
		return (NULL);
	}
	*tokens_head = current;
	node = create_ast_node(NODE_CMD, cmd, NULL, NULL);
	return (node);
}
