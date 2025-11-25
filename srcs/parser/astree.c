/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:38:27 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/25 08:49:06 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			astree_clear(t_astree *node);
void			astree_add_branch(
					t_astree *node, t_astree *left, t_astree *right);
static t_astree	*_astree_create_node(
					t_node type,
					t_cmd *cmd,
					t_astree *left,
					t_astree *right );

/*
Create new 
*/
t_astree	*astree_create_cmd_node(t_token **tokens_head, int *status)
{
	t_cmd		*cmd;
	t_astree	*node;

	cmd = tokens2cmd(tokens_head, status);
	if (cmd == NULL)
	{
		*status = 1;
		return (NULL);
	}
	node = _astree_create_node(NODE_CMD, cmd, NULL, NULL);
	if (node == NULL)
	{
		*status = 1;
		return (clear_cmd(cmd), NULL);
	}
	*status = 0;
	return (node);
}

t_astree	*astree_create_pipe_node(
	t_astree *left,
	t_astree *right,
	int *status
)
{
	t_astree	*pipe_node;

	pipe_node = _astree_create_node(NODE_PIPE, NULL, left, right);
	if (pipe_node == NULL)
	{
		*status = 1;
		return (NULL);
	}
	*status = 0;
	return (pipe_node);
}

/*Create AST tree node. */
static t_astree	*_astree_create_node(
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
	new->type = type;
	new->cmd = cmd;
	astree_add_branch(new, left, right);
	return (new);
}

/*Clears AST tree and containing t_cmd recursively.*/
void	astree_clear(t_astree *node)
{
	if (!node)
		return ;
	if (node->cmd)
	{
		clear_cmd(node->cmd);
		node->cmd = NULL;
	}
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
