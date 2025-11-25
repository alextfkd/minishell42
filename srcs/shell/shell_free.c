/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:19:27 by marvin            #+#    #+#             */
/*   Updated: 2025/11/25 08:33:14 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free t_shell object and returns t_shell->status.
 * 
 * @param shell 
 * @return int t_shell->status.
 */
int	free_shell(t_shell *shell)
{
	int	res;

	if (shell == NULL)
		return (-1);
	res = shell->status;
	if (shell->ms_buf != NULL)
		free_ms_buf(shell->ms_buf);
	free_app(shell->app);
	free(shell);
	return (res);
}

/**
 * @brief Delete the t_ms_buf memory and the all attributes inside.
 * 
 * @param ms_buf 
 */
void	free_ms_buf(t_ms_buf *ms_buf)
{
	if (ms_buf == NULL)
		return ;
	if (ms_buf->rl_buf != NULL)
	{
		free(ms_buf->rl_buf);
		ms_buf->rl_buf = NULL;
	}
	if (ms_buf->tmp_buf != NULL)
	{
		free(ms_buf->tmp_buf);
		ms_buf->tmp_buf = NULL;
	}
	if (ms_buf->sh_buf != NULL)
	{
		free(ms_buf->sh_buf);
		ms_buf->sh_buf = NULL;
	}
	free(ms_buf);
	ms_buf = NULL;
}

// Delete and NULL clear t_ms_buf->tmp_buf.
void	free_tmp_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->tmp_buf)
	{
		free(ms_buf->tmp_buf);
		ms_buf->tmp_buf = NULL;
	}
}

// Delete and NULL clear t_ms_buf->sh_buf.
void	free_shell_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->sh_buf)
	{
		free(ms_buf->sh_buf);
		ms_buf->sh_buf = NULL;
	}
}

// Delete and NULL clear t_ms_buf->rl_buf.
void	free_readline_buf(t_ms_buf *ms_buf)
{
	if (ms_buf && ms_buf->rl_buf)
	{
		free(ms_buf->rl_buf);
		ms_buf->rl_buf = NULL;
	}
}
