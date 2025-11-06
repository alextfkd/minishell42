/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 06:43:27 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*_create_empty_cmd_node(void);
void			clear_cmd(t_cmd *cmd);

t_astree	*parse_command(t_token **tokens_head)
{
	t_astree	*node;
	t_cmd		*cmd;
	t_token		*current;
	t_token		*head;

	if (!tokens_head || !(*tokens_head))
		return (NULL);
	head = *tokens_head;
	current = *tokens_head;
	cmd = _create_empty_cmd_node();
	if (!cmd)
		return (perror("minishell: t_cmd memory allocated error"), NULL);
	if (set_cmd_redirection(cmd, current))
		return (clear_cmd(cmd), NULL);
	if (set_cmd_argv(cmd, head, current))
		return (clear_cmd(cmd), NULL);
	*tokens_head = current;
	node = astree_create_node(NODE_CMD, cmd, NULL, NULL);
	return (node);
}

// free cmd list
void	clear_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->red)
		clear_red(cmd->red);
	if (cmd->argv)
		ft_free_tab(cmd->argv);
	free(cmd);
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
