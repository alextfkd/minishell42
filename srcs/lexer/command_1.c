/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/01 12:35:52 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free cmd list
void	clear_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->red)
		clear_red(cmd->red);
	if (cmd->argv)
		ft_free_tab(cmd->argv);
	free(cmd);
}

// count TK_CHAR and increment argc
int	count_argc(t_token *start, t_token *end)
{
	t_token	*current;
	int		argc;

	argc = 0;
	current = start;
	while (current != end)
	{
		if (is_red(current->tk))
		{
			if (current->next == NULL || current->next->tk != TK_CHAR)
				return (-1);
			current = current->next->next;
		}
		else if (current->tk == TK_CHAR)
		{
			argc++;
			current = current->next;
		}
		else
			return (-1);
	}
	return (argc);
}

static int	_argv_loop(t_cmd *cmd, t_token **current_ptr, int *i_ptr,
		t_token *end)
{
	t_token	*current;

	current = *current_ptr;
	while (current != end)
	{
		if (is_red(current->tk))
		{
			current = current->next->next;
		}
		else if (current->tk == TK_CHAR)
		{
			cmd->argv[*i_ptr] = ft_strdup(current->data);
			if (!cmd->argv[*i_ptr])
				return (1);
			(*i_ptr)++;
			current = current->next;
		}
	}
	*current_ptr = current;
	return (0);
}

// set values of argv
static int	_set_argv(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*current;
	int		i;

	i = 0;
	current = start;
	if (_argv_loop(cmd, &current, &i, end))
		return (1);
	cmd->argv[i] = NULL;
	return (0);
}

// handle argv
int	handle_argv(t_cmd *cmd, t_token *start, t_token *end)
{
	int	argc;

	argc = count_argc(start, end);
	if (argc < 0)
	{
		ft_putendl_fd(ERR_SYNTAX_TOKEN, 2);
		return (1);
	}
	cmd->argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!cmd->argv)
	{
		perror("minishell: t_cmd->argv memory allocated error");
		return (1);
	}
	if (_set_argv(cmd, start, end))
		return (1);
	cmd->argc = argc;
	return (0);
}
