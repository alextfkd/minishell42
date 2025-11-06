/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 11:38:26 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*_create_empty_cmd_node(void);
static int		_seek_redirection(t_cmd *cmd, t_token **current_ptr);

t_astree	*parse_command(t_token **tokens_head)
{
	t_cmd		*cmd;
	t_astree	*node;
	t_token		*current;
	t_token		*head;

	if (!tokens_head || !(*tokens_head))
		return (NULL);
	head = *tokens_head;
	current = *tokens_head;
	cmd = _create_empty_cmd_node();
	if (!cmd)
		return (perror("minishell: t_cmd memory allocated error"), NULL);
	if (_parse_cmd_loop(cmd, &current))
		return (clear_cmd(cmd), NULL);
	if (handle_argv(cmd, head, current))
		return (clear_cmd(cmd), NULL);
	*tokens_head = current;
	node = astree_create_node(NODE_CMD, cmd, NULL, NULL);
	return (node);
}

/* Create empty cmd node.*/
static t_cmd	*_create_empty_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		return (NULL);
	}
	return (cmd);
}

static int	_seek_redirection(t_cmd *cmd, t_token *current)
{
	t_token	*current;
	int		res;

	if (!cmd || !current_ptr || !(*current_ptr))
		return (1);
	current = *current_ptr;
	while (current != NULL && current->tk != TK_PIPE)
	{
		if (is_red(current->tk))
		{
			res = append_red_to_cmd(cmd, current_ptr);
			if (res == 1)
				return (1);
		}
		current = current->next;
	}
	*current_ptr = current;
	return (0);
}
