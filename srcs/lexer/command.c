/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 06:50:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free cmd list
void	clear_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if(cmd->red)
		clear_red(cmd->red);
	if (cmd->argv)
		ft_free_tab(cmd->argv);
	free(cmd);
}

// create new cmd node
t_cmd *_create_cmd_node()
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		perror("minishell: t_cmd memory allocated error");
		return (NULL);
	}
	return (cmd);
}

// set values of argv
void set_argv(t_cmd *cmd,t_token *start,t_token *end)
{
	t_token *current;
	int i;

	i = 0;
	current = start;
	while(current != end)
	{
		if (is_red(current->tk))
		{
			if (current->next != NULL)
				current = current->next->next;
			else
				break;
		}
		else if (current->tk == TK_CHAR)
		{

			cmd->argv[i] = current->data;
			i++;
			current = current->next;
		}
		else
			current = current->next;
	}
	cmd->argv[i] = NULL;
}

// handle argv
int handle_argv(t_cmd *cmd,t_token *start,t_token *end)
{
	int argc;

    argc = count_args(start, end);
    if (argc < 0)
        return (1);

    cmd->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
    if (!cmd->argv)
	{
		perror("minishell: t_cmd->argv memory allocated error");
        return (1);
	}
    set_argv(cmd, start, end);
    cmd->argc = argc;
    return (0);
}

t_astree *parse_command(t_token **tokens_head)
{
	t_cmd		*cmd;
	t_astree	*node;
	t_token		*current;
	t_token		*head;

	cmd = create_cmd_node();
	head = *tokens_head;
	current = head;
	while(current != NULL && current->tk != TK_PIPE)
	{
		if(is_red(current->tk))
		{
			if(handle_red(cmd, &current))
			{
				clear_cmd(cmd);
				return (NULL);
			}
		}
		else
		{
			current = current->next;
		}
	}
	if(handle_argv(cmd, head, current))
	{
		clear_cmd(cmd);
		return (NULL);
	}

	*tokens_head = current;
	node = create_ast_node(NODE_CMD, cmd, NULL,NULL);
	return (node);
}
