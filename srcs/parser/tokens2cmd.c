/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/04 09:17:04 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERR_CMD_MALLOC "minishell: t_cmd memory allocated error"
#define ERR_CMD_RED "minishell: set_cmd_redirection() error"
#define ERR_CMD_ARGV "minishell: set_cmd_argv() error"

static t_cmd	*_create_empty_cmd_node(int *status);
void			clear_cmd(t_cmd **cmd);

/* Parse tokens and create a new t_cmd.
This function will automatically set command redirection and args
to the newly created t_cmd. Returns NULL if failed.
*/
t_cmd	*tokens2cmd(t_token **tokens_head, int *status)
{
	t_cmd		*cmd;
	t_token		*current;
	t_token		*head;

	if (!tokens_head || !(*tokens_head))
		return (NULL);
	head = *tokens_head;
	current = *tokens_head;
	cmd = _create_empty_cmd_node(status);
	if (!cmd)
		return (ft_putendl_fd(ERR_CMD_MALLOC, 2), NULL);
	if (set_cmd_redirection(cmd, &current, status) != 0)
	{
		clear_cmd(&cmd);
		return (ft_putendl_fd(ERR_CMD_RED, 2), NULL);
	}
	if (set_cmd_argv(cmd, head, current) != 0)
	{
		*status = 1;
		clear_cmd(&cmd);
		return (ft_putendl_fd(ERR_CMD_ARGV, 2), NULL);
	}
	*tokens_head = current;
	return (cmd);
}

// Free t_cmd. This will free t_cmd->red and t_cmd->argv simltaneously.
void	clear_cmd(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	if ((*cmd)->red)
	{
		clear_red(&(*cmd)->red);
		(*cmd)->red = NULL;
	}
	if ((*cmd)->argv)
	{
		ft_free_tab((*cmd)->argv);
		(*cmd)->argv = NULL;
	}
	free(*cmd);
	*cmd = NULL;
}

/* Create empty cmd node.*/
static t_cmd	*_create_empty_cmd_node(int *status)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		*status = 1;
		return (NULL);
	}
	*status = 0;
	return (cmd);
}
