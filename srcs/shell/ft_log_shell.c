/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 02:31:48 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/18 02:32:14 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
