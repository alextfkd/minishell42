/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_buf_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:19:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/17 08:23:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Delete the t_ms_buf memory and the all attributes inside.
void	delete_ms_buf(t_ms_buf *ms_buf)
{
	if (ms_buf == NULL)
		return ;
	if (ms_buf->rl_buf != NULL)
		free(ms_buf->rl_buf);
	if (ms_buf->tmp_buf != NULL)
		free(ms_buf->tmp_buf);
	if (ms_buf->sh_buf != NULL)
		free(ms_buf->sh_buf);
	free(ms_buf);
}

void	free_tmp_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->tmp_buf)
	{
		free(ms_buf->tmp_buf);
		ms_buf->tmp_buf = NULL;
	}
}

void	free_shell_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->sh_buf)
	{
		free(ms_buf->sh_buf);
		ms_buf->sh_buf = NULL;
	}
}

void	free_readline_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->rl_buf)
	{
		free(ms_buf->rl_buf);
		ms_buf->rl_buf = NULL;
	}
}
