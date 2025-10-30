/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 15:13:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_red(t_tkind tk)
{
	return (tk == TK_RED_OUT || tk == TK_RED_APPEND || tk == TK_RED_IN || tk == TK_RED_HEREDOC );
}

// count TK_CHAR and increment argc
int count_tk_char(t_token *start,t_token *end)
{
	t_token	*current;
	int		argc;
	argc = 0;
	current = start;
	while(current != end)
	{
		if(is_red(current->tk))
		{
			if(current->next == NULL || current->next->tk != TK_CHAR)
			{
				ft_putendl_fd(ERR_SYNTAX_TOKEN,2);
				return (-1);
			}
				current = current->next->next;
		}
		else if (current->tk == TK_CHAR)
		{
			argc++;
			current = current->next;
		}
		else
		{
			ft_putendl_fd(ERR_SYNTAX_TOKEN,2);
			return (-1);
		}
	}
	return (argc);
}

t_astree	*parse_pipeline(t_token **tokens_head)
{
	t_astree *left_node;
	t_astree *right_node;
	t_astree *pipe_root;

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
			ft_putendl_fd("|",2);
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
