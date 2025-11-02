/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/10/25 15:11:05 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = create_t_shell(argc, argv);
	if (shell == NULL)
		return (1);
	if (shell->argc == 1)
		shell->status = interactive_shell(shell, envp);
	else if (shell->argc >= 2)
		shell->status = non_interactive_shell(shell, envp);
	else
	{
		shell->status = 1;
		return (free_t_shell(shell));
	}
	return (free_t_shell(shell));
}
