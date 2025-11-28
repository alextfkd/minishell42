/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 08:24:20 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		_pipe_syntax_err(t_token *head);
static int		_if_no_pipe_token(t_token *tokens_head);
static t_astree	*_astree_attach_right(
					t_astree *root, t_token **tokens_head, int *status);

t_astree	*create_astree_from_tokens(t_token **head, int *status)
{
	t_astree	*astree_root;
	t_astree	*new_root;
	t_token		*original_head;

	if (!head || !(*head))
		return (NULL);
	if ((*head)->tk == TK_PIPE || token_last(*head)->tk == TK_PIPE)
		return (_pipe_syntax_err(*head), NULL);
	original_head = *head;
	astree_root = astree_create_cmd_node(head, status);
	if (!astree_root || _if_no_pipe_token(original_head))
		return (free_tokens(original_head), astree_root);
	while (*head != NULL && (*head)->tk == TK_PIPE)
	{
		new_root = _astree_attach_right(astree_root, head, status);
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

static void	_pipe_syntax_err(t_token *head)
{
	free_tokens(head);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(ERR_SYNTAX_TOKEN_PIPE, 2);
	return ;
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
