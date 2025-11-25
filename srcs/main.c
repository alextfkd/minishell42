/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/11/25 08:43:01 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

static void	_configure_rl_signals(void);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	_configure_rl_signals();
	shell = create_t_shell(argc, argv, envp);
	if (shell == NULL)
		return (1);
	if (shell->argc == 1)
		shell->status = interactive_shell(shell);
	else if (shell->argc >= 2)
		shell->status = non_interactive_shell(shell);
	else
	{
		shell->status = 1;
		return (free_shell(shell));
	}
	free_tokens(shell->app->token_head);
	free_list(&(shell->app->cmd_list));
	return (free_shell(shell));
}

static void	_configure_rl_signals(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
}
