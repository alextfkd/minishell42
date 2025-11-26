/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree2list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:48:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 23:04:47 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Recursively converts a pipeline represented in an Abstract Syntax
 * Tree (AST) into a simple linked list of command structures (t_list).
 * * This function processes nodes of type NODE_PIPE and NODE_CMD.
 * It uses a depth-first approach to traverse the left side
 * (which contains the start of the pipeline) and then appends
 * the command from the right side.
 *
 * @param node
 * @return t_list*
 */
t_list	*astree2list(t_astree *node)
{
	t_list	*cmd_list;
	t_list	*new_node;

	if (!node)
		return (NULL);
	if (node->type == NODE_PIPE)
	{
		cmd_list = astree2list(node->left);
		if (!cmd_list)
			return (NULL);
		if (node->right && node->right->type == NODE_CMD)
		{
			new_node = ft_lstnew(node->right->cmd);
			if (!new_node)
				return (free_list(&cmd_list), NULL);
			ft_lstadd_back(&cmd_list, new_node);
		}
		return (cmd_list);
	}
	else if (node->type == NODE_CMD)
		return (ft_lstnew(node->cmd));
	return (NULL);
}

/**
 * @brief free pipeline lists
 *
 * @param list
 */
void	free_list(t_list **list)
{
	t_list	*current;
	t_list	*next_node;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next_node = current->next;
		if (current->content != NULL)
		{
			clear_cmd((t_cmd **) &(current->content));
			current->content = NULL;
		}
		free(current);
		current = next_node;
	}
	*list = NULL;
}
