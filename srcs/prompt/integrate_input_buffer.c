/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate_input_buffer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:25:27 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/12/02 12:28:58 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*_integrate_buffers(t_ms_buf *ms_buf);
static	int		_is_executable(t_ms_buf *ms_buf, int *status);
static t_token	*get_token_tail(t_token *head);
static void		_free_tmp_and_rl_buf(t_ms_buf *ms_buf);

char	*integrate_input_buffer(t_shell *shell)
{
	t_ms_buf	*ms_buf;
	int			status;

	ms_buf = shell->ms_buf;
	ms_buf->sh_buf = _integrate_buffers(shell->ms_buf);
	status = 0;
	if (ms_buf->sh_buf == NULL)
		status = 1;
	else if (ft_strnstr(ms_buf->sh_buf, "\\\\", ft_strlen(ms_buf->sh_buf)))
	{
		status = 1;
		ft_putendl_fd(ERR_DOUBLE_BACKSLASH, 2);
	}
	if (status)
	{
		_free_tmp_and_rl_buf(ms_buf);
		return (free_shell_buf(ms_buf), NULL);
	}
	if (_is_executable(ms_buf, &(shell->status)) == 0)
	{
		_free_tmp_and_rl_buf(ms_buf);
		ms_buf->tmp_buf = ft_strdup(ms_buf->sh_buf);
		return (free_shell_buf(ms_buf), NULL);
	}
	return (_free_tmp_and_rl_buf(ms_buf), ms_buf->sh_buf);
}

static void	_free_tmp_and_rl_buf(t_ms_buf *ms_buf)
{
	free_tmp_buf(ms_buf);
	free_readline_buf(ms_buf);
}

static char	*_integrate_buffers(t_ms_buf *ms_buf)
{
	char	*integrated_buf;

	if (!ms_buf || ms_buf->rl_buf == NULL)
		return (NULL);
	if (ms_buf->tmp_buf == NULL)
		integrated_buf = ft_strdup(ms_buf->rl_buf);
	else
		integrated_buf = ft_strjoin(ms_buf->tmp_buf, ms_buf->rl_buf);
	if (integrated_buf == NULL)
	{
		perror("Buffer integration error.");
		free_ms_buf(&ms_buf);
		return (NULL);
	}
	return (integrated_buf);
}

static	int	_is_executable(t_ms_buf *ms_buf, int *status)
{
	t_token	*token;

	token = tokenize(ms_buf->sh_buf, status);
	if (token == NULL)
		return (-1);
	if (get_token_tail(token)->tk == TK_ESCAPED_NL
		&& ms_buf->rl_buf && ft_strcmp(ms_buf->rl_buf, "\n") != 0)
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
