/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:21:26 by marvin            #+#    #+#             */
/*   Updated: 2025/10/25 14:25:20 by tkatsuma         ###   ########.fr       */
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

void	log_debug_ms_buf(t_shell *shell)
{
	t_ms_buf	*ms_buf;

	ms_buf = shell->ms_buf;
	if (shell->loglevel <= LOG_DEBUG)
	{
		printf("ms_buf->rl_buf  = %s\n", ms_buf->rl_buf);
		printf("ms_buf->tmp_buf = %s\n", ms_buf->tmp_buf);
		printf("ms_buf->sh_buf  = %s\n", ms_buf->sh_buf);
	}
}
