/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_astree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:25:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 16:12:21 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get node type
static const char	*_get_node_type(t_node type)
{
	if (type == NODE_CMD)
		return ("NODE_CMD");
	else if (type == NODE_PIPE)
		return ("NODE_PIPE");
	else
		return ("UNKNOWN_NODE");
}

static void	_print_ast_node(t_astree *node)
{
	int	i;

	printf("├── %s", _get_node_type(node->type));
	if (node->type == NODE_CMD)
	{
		printf(" [argc: %d]", node->cmd->argc);
		printf(" (Args: [");
		i = 0;
		while (node->cmd->argv && node->cmd->argv[i])
		{
			printf("'%s'", node->cmd->argv[i]);
			if (node->cmd->argv[i + 1])
				printf(", ");
			i++;
		}
		printf("]");
		if (node->cmd->red)
			printf(" + Reds...)");
		else
			printf(")");
	}
}

static void	_print_ast_indent(t_astree *node, int level)
{
	int	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < level)
	{
		printf("│   ");
		i++;
	}
	_print_ast_node(node);
	printf("\n");
	_print_ast_indent(node->left, level + 1);
	_print_ast_indent(node->right, level + 1);
}

void	log_debug_show_ast(t_astree *root, t_loglevel log_level)
{
	log_debug("--- Abstract Syntax Tree Start ---", log_level);
	if (root == NULL)
	{
		log_debug("AST is NULL (Parse Error or Empty Input)", log_level);
	}
	else
	{
		if (log_level == LOG_DEBUG)
			_print_ast_indent(root, 0);
	}
	log_debug("---- Abstract Syntax Tree End ----", log_level);
}
