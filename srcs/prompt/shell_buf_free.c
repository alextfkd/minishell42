/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_buf_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:19:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/25 14:58:06 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Delete the t_ms_buf memory and the all attributes inside.
void	free_ms_buf(t_ms_buf *ms_buf)
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
