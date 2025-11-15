/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/15 13:17:10 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_astree	*_handle_pipe_sequence(
					t_token **tokens_head,
					t_astree *current_pipe_root);

t_astree	*create_astree_from_tokens(t_token **tokens_head)
{
	t_astree	*root_node;
	t_token		*original_head;

	original_head = *tokens_head;
	root_node = astree_create_cmd_node(tokens_head);
	if (!root_node)
		return (NULL);
	while (*tokens_head != NULL && (*tokens_head)->tk == TK_PIPE)
	{
		root_node = _handle_pipe_sequence(tokens_head, root_node);
		if (!root_node)
			return (astree_clear(root_node), NULL);
	}
	free_tokens(original_head);
	*tokens_head = NULL;
	return (root_node);
}

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
