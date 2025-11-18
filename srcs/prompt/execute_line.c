/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:26:24 by marvin            #+#    #+#             */
/*   Updated: 2025/10/17 09:28:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		_is_executable(char *rl_buf);
static t_token	*get_token_tail(t_token *head);

char	*concat_rl_buffer(t_shell *shell)
{
	t_ms_buf	*ms_buf;
	int			*status;
	t_loglevel	log_level;

	ms_buf = shell->ms_buf;
	status = &(shell->status);
	log_level = shell->loglevel;
	if (ms_buf->rl_buf == NULL)
		return (NULL);
	if (ms_buf->tmp_buf == NULL)
		ms_buf->sh_buf = ft_strdup(ms_buf->rl_buf);
	else
		ms_buf->sh_buf = ft_strjoin(ms_buf->tmp_buf, ms_buf->rl_buf);
	free_tmp_buf(ms_buf);
	free_readline_buf(ms_buf);
	if (_is_executable(ms_buf->sh_buf) == 0)
	{
		ms_buf->tmp_buf = ft_strdup(ms_buf->sh_buf);
		return (free_shell_buf(ms_buf), NULL);
	}
	return (ms_buf->sh_buf);
	*status = execute_cmd(ms_buf->sh_buf, shell->app, log_level);
	free_shell_buf(ms_buf);
}

void	exec_line(t_shell *shell)
{
	t_ms_buf	*ms_buf;
	int			*status;
	t_loglevel	log_level;

	ms_buf = shell->ms_buf;
	status = &(shell->status);
	log_level = shell->loglevel;
	if (ms_buf->rl_buf == NULL)
		return ;
	if (ms_buf->tmp_buf == NULL)
		ms_buf->sh_buf = ft_strdup(ms_buf->rl_buf);
	else
		ms_buf->sh_buf = ft_strjoin(ms_buf->tmp_buf, ms_buf->rl_buf);
	free_tmp_buf(ms_buf);
	free_readline_buf(ms_buf);
	if (_is_executable(ms_buf->sh_buf) == 0)
	{
		ms_buf->tmp_buf = ft_strdup(ms_buf->sh_buf);
		return (free_shell_buf(ms_buf));
	}
	*status = execute_cmd(ms_buf->sh_buf, shell->app, log_level);
	free_shell_buf(ms_buf);
}

static	int	_is_executable(char *rl_buf)
{
	t_token	*token;

	token = tokenize(rl_buf);
	if (token == NULL)
		return (-1);
	if (get_token_tail(token)->tk == TK_ESCAPED_NL)
	{
		free_tokens(token);
		return (0);
	}
	if (token->state == S_NORMAL)
	{
		free_tokens(token);
		return (1);
	}
	log_debug_show_token(get_token_tail(token), LOG_DEBUG);
	free_tokens(token);
	return (0);
}

/**
 * @brief Get the token tail object. 
 * 
 * @param head 
 * @return t_token* Returns NULL if head is NULL.
 */
static t_token	*get_token_tail(t_token *head)
{
	t_token	*tail;

	if (head == NULL)
		return (NULL);
	tail = head;
	while (tail != NULL && tail->next != NULL)
		tail = tail->next;
	return (tail);
}
