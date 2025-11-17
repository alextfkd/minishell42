/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/16 13:10:43 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		_if_no_pipe_token(t_token *tokens_head);
static t_astree	*_astree_attach_right(t_astree *root, t_token **tokens_head);

t_astree	*create_astree_from_tokens(t_token **tokens_head)
{
	t_astree	*astree_root;
	t_astree	*new_root;
	t_token		*original_head;

	original_head = *tokens_head;
	astree_root = astree_create_cmd_node(tokens_head);
	if (!astree_root)
		return (NULL);
	if (_if_no_pipe_token(original_head))
		return (free_tokens(original_head), astree_root);
	while (*tokens_head != NULL && (*tokens_head)->tk == TK_PIPE)
	{
		new_root = _astree_attach_right(astree_root, tokens_head);
		if (new_root == NULL)
		{
			free_tokens(original_head);
			astree_clear(astree_root);
			return (NULL);
		}
		astree_root = new_root;
	}
	free_tokens(original_head);
	return (astree_root);
}

static t_astree	*_astree_attach_right(t_astree *root, t_token **tokens_head)
{
	t_astree	*new_root;

	new_root = astree_create_pipe_node(root, NULL);
	if (new_root == NULL)
	{
		return (NULL);
	}
	*tokens_head = (*tokens_head)->next;
	new_root->right = astree_create_cmd_node(tokens_head);
	if (!new_root->right)
	{
		new_root->left = NULL;
		return (astree_clear(new_root), NULL);
	}
	return (new_root);
}

static int	_if_no_pipe_token(t_token *tokens_head)
{
	t_token	*head;

	head = tokens_head;
	while (head != NULL)
	{
		if (head->tk == TK_PIPE)
			return (0);
		head = head->next;
	}
	return (1);
}

/*
static t_astree	*_handle_pipe_sequence(t_token **tokens_head,
		t_astree *current_pipe_root)
{
	t_astree	*right_node;

	*tokens_head = (*tokens_head)->next;
	if (*tokens_head == NULL)
	{
		ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
		ft_putendl_fd(" \'|\'", 2);
		astree_clear(current_pipe_root);
		return (NULL);
	}
	right_node = astree_create_cmd_node(tokens_head);
	if (!right_node)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	current_pipe_root = astree_create_pipe_node(current_pipe_root, right_node);
	if (!current_pipe_root)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	return (current_pipe_root);
}
*/

/*
static t_astree	*_handle_pipe_sequence(t_token **tokens_head,
		t_astree *current_pipe_root)
{
	t_astree	*right_node;

	*tokens_head = (*tokens_head)->next;
	if (*tokens_head == NULL)
	{
		ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
		ft_putendl_fd(" \'|\'", 2);
		astree_clear(current_pipe_root);
		return (NULL);
	}
	right_node = astree_create_cmd_node(tokens_head);
	if (!right_node)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	current_pipe_root = astree_create_pipe_node(current_pipe_root, right_node);
	if (!current_pipe_root)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	return (current_pipe_root);
}
*/
