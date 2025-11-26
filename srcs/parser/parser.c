/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 22:45:11 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		_if_no_pipe_token(t_token *tokens_head);
static t_astree	*_astree_attach_right(
					t_astree *root, t_token **tokens_head, int *status);

t_astree	*create_astree_from_tokens(t_token **tokens_head, int *status)
{
	t_astree	*astree_root;
	t_astree	*new_root;
	t_token		*original_head;

	if (!tokens_head || !(*tokens_head))
		return (NULL);
	original_head = *tokens_head;
	astree_root = astree_create_cmd_node(tokens_head, status);
	if (!astree_root)
		return (free_tokens(original_head), NULL);
	if (_if_no_pipe_token(original_head))
		return (free_tokens(original_head), astree_root);
	while (*tokens_head != NULL && (*tokens_head)->tk == TK_PIPE)
	{
		new_root = _astree_attach_right(astree_root, tokens_head, status);
		if (new_root == NULL)
		{
			*status = 1;
			astree_clear(&astree_root);
			return (free_tokens(original_head), NULL);
		}
		astree_root = new_root;
	}
	return (free_tokens(original_head), astree_root);
}

static t_astree	*_astree_attach_right(
	t_astree *root,
	t_token **tokens_head,
	int *status
)
{
	t_astree	*new_root;

	new_root = astree_create_pipe_node(root, NULL, status);
	if (new_root == NULL)
	{
		*status = 1;
		return (NULL);
	}
	*tokens_head = (*tokens_head)->next;
	new_root->right = astree_create_cmd_node(tokens_head, status);
	if (!new_root->right)
	{
		new_root->left = NULL;
		return (astree_clear(&new_root), NULL);
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
