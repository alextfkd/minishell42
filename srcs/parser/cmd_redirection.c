/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:44:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/22 06:57:28 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_red	*_create_red_node(t_tkind tk, char *file, int is_quoted);
static int		_validate_red_target(t_token *target);
static int		_append_red_to_cmd(t_cmd *cmd, t_token *current);
static int		_is_red_target_quoted(t_token *target);

/* Create redirection node (t_red) and append on (or create) t_cmd->red.
The new redirection node is created from the current token (operator) and
the next token (redirection target).
**current pointer will be moved to either NULL or TK_PIPE node.*/
int	set_cmd_redirection(t_cmd *cmd, t_token **current, int *status)
{
	t_token	*p_token;
	int		res;

	if (!cmd || *status == 1)
	{
		*status = 1;
		return (1);
	}
	p_token = *current;
	while (p_token != NULL && p_token->tk != TK_PIPE)
	{
		if (is_red(p_token->tk))
		{
			res = _append_red_to_cmd(cmd, p_token);
			if (res == 1)
			{
				*status = 1;
				return (1);
			}
		}
		p_token = p_token->next;
	}
	*current = p_token;
	return (0);
}

/* Create redirection node (t_red) and append on (or create) t_cmd->red.
The new redirection node is created from the current token (operator) and
the next token (redirection target).*/
static int	_append_red_to_cmd(t_cmd *cmd, t_token *current)
{
	t_token	*operator;
	t_token	*target;
	char	*target_data;
	t_red	*redirection_node;

	if (!cmd || !current)
		return (1);
	operator = current;
	target = operator->next;
	if (_validate_red_target(target))
		return (1);
	target_data = ft_strdup(target->data);
	if (!target_data)
		return (perror("minishell: red->data memory allocation error"), 1);
	redirection_node = _create_red_node(
			operator->tk,
			target_data,
			_is_red_target_quoted(target));
	if (!redirection_node)
		return (perror("minishell: t_red memory allocated error"), 1);
	else if (cmd->red == NULL)
		cmd->red = redirection_node;
	else
		red_add_back(&(cmd->red), redirection_node);
	return (0);
}

// Create a new redirection node (t_red).
static t_red	*_create_red_node(t_tkind tk, char *file, int is_quoted)
{
	t_red	*new;

	if (file == NULL)
		return (NULL);
	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (NULL);
	new->tk = tk;
	new->file = file;
	new->is_quoted = is_quoted;
	new->next = NULL;
	return (new);
}

/* Returns 1 if t_token is NULL or t_token->tk is not TK_CHAR;
Otherwise returns 0.*/
static int	_validate_red_target(t_token *target)
{
	if (target == NULL)
	{
		ft_putstr_fd("error(103)", 2);
		ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
		ft_putendl_fd(" \'newline\'", 2);
		return (1);
	}
	if (target->tk != TK_CHAR)
	{
		ft_putstr_fd("error(110)", 2);
		ft_putendl_fd(ERR_SYNTAX_TOKEN, 2);
		return (1);
	}
	return (0);
}

static int	_is_red_target_quoted(t_token *target)
{
	if (!target || target->tk != TK_CHAR)
		return (0);
	if (target->state != S_NORMAL)
		return (1);
	if (ft_strchr(target->data, '\"') || ft_strchr(target->data, '\''))
		return (1);
	return (0);
}
