/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:38:27 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 16:47:24 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	_astree_set_type(t_astree *node, t_node type)
{
	if (!node)
		return ;
	node->type = type;
}

static void	_astree_set_cmd(t_astree *node, t_cmd *cmd)
{
	if (!node || !cmd)
		return ;
	node->cmd = cmd;
}

void	clear_astree(t_astree *node)
{
	if (!node)
		return ;
	if (node->cmd)
		clear_cmd(node->cmd);
	clear_astree(node->left);
	clear_astree(node->right);
	free(node);
}

void	astree_add_branch(t_astree *root, t_astree *left, t_astree *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

t_astree	*create_ast_node(
		t_node type,
		t_cmd *cmd,
		t_astree *left,
		t_astree *right )
{
	t_astree	*new;

	new = ft_calloc(1, sizeof(t_astree));
	if (!new)
	{
		perror("minishell: t_astree memory allocated error");
		if (cmd)
			clear_cmd(cmd);
		clear_astree(left);
		clear_astree(right);
		return (NULL);
	}
	_astree_set_type(new, type);
	_astree_set_cmd(new, cmd);
	astree_add_branch(new, left, right);
	return (new);
}
