/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/10/20 06:19:51 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	int			exit_status;
	t_loglevel	log_level;

	log_level = LOG_DEBUG;
	log_level = LOG_QUIET;
	if (argc == 1)
		exit_status = interactive_shell(argc, argv, envp, log_level);
	else if (argc >= 2)
		exit_status = non_interactive_shell(argc, argv, envp, log_level);
	else
		return (1);
	return (exit_status);
}
