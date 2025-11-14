/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/15 06:04:43 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*_create_empty_cmd_node(void);
void			clear_cmd(t_cmd *cmd);

t_cmd	*tokens2cmd(t_token **tokens_head)
{
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
	log_debug("cmd set", LOG_DEBUG);
	if (set_cmd_redirection(cmd, &current) != 0)
		log_debug("current is NULL", LOG_DEBUG);
	log_debug("red set", LOG_DEBUG);
	if (set_cmd_argv(cmd, head, current))
		return (clear_cmd(cmd), NULL);
	log_debug("argv set", LOG_DEBUG);
	*tokens_head = current;
	return (cmd);
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
