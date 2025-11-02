/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:44:01 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/03 02:06:32 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check error

static int	_print_file_error(t_token *file)
{
	if (file == NULL)
	{
		ft_putstr_fd(ERR_SYNTAX_TOKEN, 2);
		ft_putendl_fd(" \'newline\'", 2);
		return (1);
	}
	if (file->tk != TK_CHAR)
	{
		ft_putendl_fd(ERR_SYNTAX_TOKEN, 2);
		return (1);
	}
	return (0);
}

// handle redirection
int	handle_red(t_cmd *cmd, t_token **current)
{
	t_token	*operator;
	t_token	*file;
	char	*new_data;
	t_red	*new_red;

	operator = *current;
	file = operator->next;
	if (_print_file_error(file))
		return (1);
	new_data = ft_strdup(file->data);
	if (!new_data)
	{
		perror("minishell: red->data memory allocation error");
		return (1);
	}
	new_red = create_red_node(operator->tk, new_data);
	if (!new_red)
		return (1);
	red_add_back(&(cmd->red), new_red);
	*current = operator->next->next;
	return (0);
}

// create new redirection node
t_red	*create_red_node(t_tkind tk, char *file)
{
	t_red	*new;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
	{
		perror("minishell: t_red memory allocated error");
		return (NULL);
	}
	new->tk = tk;
	new->file = file;
	new->next = NULL;
	return (new);
}
