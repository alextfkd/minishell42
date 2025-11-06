/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/05 00:09:03 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_astree	*_handle_pipe_sequence(
					t_token **tokens_head,
					t_astree *current_pipe_root);

t_astree	*parse_pipeline(t_token **tokens_head)
{
	t_astree	*pipe_root;

	pipe_root = parse_command(tokens_head);
	if (!pipe_root)
		return (NULL);
	while (*tokens_head != NULL && (*tokens_head)->tk == TK_PIPE)
	{
		pipe_root = _handle_pipe_sequence(tokens_head, pipe_root);
		if (!pipe_root)
			return (NULL);
	}
	return (pipe_root);
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
	right_node = parse_command(tokens_head);
	if (!right_node)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	current_pipe_root = astree_create_node(NODE_PIPE, NULL, current_pipe_root,
			right_node);
	if (!current_pipe_root)
	{
		astree_clear(current_pipe_root);
		return (NULL);
	}
	return (current_pipe_root);
}
