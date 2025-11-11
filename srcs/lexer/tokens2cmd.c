/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/10 23:13:44 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*_create_empty_cmd_node(void);
void			clear_cmd(t_cmd *cmd);

/* Parse tokens and create a new t_cmd. This function will automatically set
command redirection and args to the newly created t_cmd. 
Returns NULL if failed.
*/
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

// Free t_cmd. This will free t_cmd->red and t_cmd->argv simltaneously.
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
