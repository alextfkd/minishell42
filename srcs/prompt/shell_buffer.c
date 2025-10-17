/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:21:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/16 09:26:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create t_ms_buf
// rl_buf: readline() buffer.
// tmp_buf: tempolary buffer, used when the command is separated with \newline.
// sh_buf: buffer passed to execute_shell().
t_ms_buf	*create_ms_buf(void)
{
	t_ms_buf	*ms_buf;

	ms_buf = (t_ms_buf *)malloc(sizeof(t_ms_buf));
	if (ms_buf == NULL)
		return (NULL);
	ft_memset(ms_buf, '\0', sizeof(t_ms_buf));
	ms_buf->rl_buf = NULL;
	ms_buf->tmp_buf = NULL;
	ms_buf->sh_buf = NULL;
	return (ms_buf);
}

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

void	log_debug_ms_buf(t_ms_buf *ms_buf, t_loglevel log_level)
{
	if (log_level <= LOG_DEBUG)
	{
		printf("ms_buf->rl_buf  = %s\n", ms_buf->rl_buf);
		printf("ms_buf->tmp_buf = %s\n", ms_buf->tmp_buf);
		printf("ms_buf->sh_buf  = %s\n", ms_buf->sh_buf);
	}
}
