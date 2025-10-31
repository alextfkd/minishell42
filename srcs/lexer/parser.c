/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 16:39:12 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*parse_pipeline(t_token **tokens_head)
{
	t_astree	*left_node;
	t_astree	*right_node;
	t_astree	*pipe_root;

	left_node = parse_command(tokens_head);
	if (!left_node)
		return (NULL);
	pipe_root = left_node;
	while (*tokens_head != NULL && (*tokens_head)->tk == TK_PIPE)
	{
		*tokens_head = (*tokens_head)->next;
		if (*tokens_head == NULL)
		{
			ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
			ft_putendl_fd("|", 2);
			clear_astree(pipe_root);
			return (NULL);
		}
		right_node = parse_command(tokens_head);
		if (!right_node)
		{
			clear_astree(pipe_root);
			return (NULL);
		}
		pipe_root = create_ast_node(NODE_PIPE, NULL, pipe_root, right_node);
		if (!pipe_root)
		{
			clear_astree(pipe_root);
			return (NULL);
		}
	}
	return (pipe_root);
}
