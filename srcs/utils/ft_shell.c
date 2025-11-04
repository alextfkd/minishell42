/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:09:57 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/30 11:27:18 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*create_t_shell(int argc, char **argv)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (shell == NULL)
		return (NULL);
	shell->ms_buf = create_ms_buf();
	if (shell->ms_buf == NULL)
		return (free(shell), NULL);
	shell->argc = argc;
	shell->argv = argv;
	shell->loglevel = LOGLEVEL;
	shell->status = SHELL_SUCCESS;
	return (shell);
}

t_status	free_t_shell(t_shell *shell)
{
	t_status	res;

	res = shell->status;
	free_ms_buf(shell->ms_buf);
	free(shell);
	return (res);
}
