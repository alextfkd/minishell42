/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:38 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/28 03:26:37 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_interactive_shell(t_shell *shell)
{
	int	i;

	log_debug("MINISHELL NON-INTERACTIVE MODE", shell->loglevel);
	i = 1;
	while (i < shell->argc)
	{
		shell->ms_buf->rl_buf = ft_strjoin(shell->argv[i++], " ");
		if (shell->ms_buf->rl_buf == NULL)
			return (free_ms_buf(&(shell->ms_buf)), 1);
		if (shell->ms_buf->tmp_buf == NULL)
			shell->ms_buf->sh_buf = ft_strdup(shell->ms_buf->rl_buf);
		else
			shell->ms_buf->sh_buf = ft_strjoin(
					shell->ms_buf->tmp_buf, shell->ms_buf->rl_buf);
		if (shell->ms_buf->sh_buf == NULL)
			return (free_ms_buf(&(shell->ms_buf)), 1);
		if (i != shell->argc)
			shell->ms_buf->tmp_buf = shell->ms_buf->sh_buf;
	}
	pipeline_executor(shell);
	return (0);
}
