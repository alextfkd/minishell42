/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/10/16 14:10:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	main(int argc, char **argv)
{
	int			exit_status;
	t_loglevel	log_level;

	log_level = LOG_QUIET;
	log_level = LOG_DEBUG;
	if (argc == 1)
		exit_status = interactive_shell(argc, argv, log_level);
	else if (argc >= 2)
		exit_status = non_interactive_shell(argc, argv, log_level);
	else
		return (1);
	return (exit_status);
}
