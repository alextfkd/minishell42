/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:09:57 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/17 12:05:48 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*create_t_shell(int argc, char **argv, char **envp)
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
	shell->status = 0;
	shell->app = setup_app(envp, &(shell->status));
	if (shell->app == NULL)
		return (NULL);
	return (shell);
}

int	free_t_shell(t_shell *shell)
{
	int	res;

	res = shell->status;
	free_ms_buf(shell->ms_buf);
	free_app(shell->app);
	free(shell);
	return (res);
}
