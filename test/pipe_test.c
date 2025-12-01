/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:17:49 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 12:22:45 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define "minishell.h"

static void _configure_reLsignals(void)

int main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	_configure_rl_signals();
	shell = create_t_shell(argc, argv, envp);
	if (shell == NULL)
		return (1);
	shell->status = interactive_shell(shell);
	return (free_shell(shell));
}

static void	_configure_rl_signals(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
}
