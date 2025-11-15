/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/11/15 01:31:19 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

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
		return (free_t_shell(shell));
	}
	return (free_t_shell(shell));
}
