/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:38:27 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/05 00:00:39 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_astree_set_type(t_astree *node, t_node type);
static void	_astree_set_cmd(t_astree *node, t_cmd *cmd);
void		astree_clear(t_astree *node);
void		astree_add_branch(t_astree *node, t_astree *left, t_astree *right);

/*Create AST tree node. */
t_astree	*astree_create_node(
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
		clear_cmd(cmd);
		astree_clear(left);
		astree_clear(right);
		return (NULL);
	}
	_astree_set_type(new, type);
	_astree_set_cmd(new, cmd);
	astree_add_branch(new, left, right);
	return (new);
}

/*Clears AST tree recursively.*/
void	astree_clear(t_astree *node)
{
	if (!node)
		return ;
	if (node->cmd)
		clear_cmd(node->cmd);
	astree_clear(node->left);
	astree_clear(node->right);
	free(node);
}

/*Add left and right branch nodes.*/
void	astree_add_branch(t_astree *node, t_astree *left, t_astree *right)
{
	if (!node)
		return ;
	node->left = left;
	node->right = right;
}

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
