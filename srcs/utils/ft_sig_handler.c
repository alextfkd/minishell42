/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:14:43 by marvin            #+#    #+#             */
/*   Updated: 2025/10/16 02:37:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_loglevel_notice(void);

// Exit minishell without message to STDOUT.
// The status code upon exit is 0.
void	sigint_handler(int signal)
{
	t_loglevel	log_level;

	_loglevel_notice();
	log_level = LOG_QUIET;
	if (signal == SIGINT)
	{
		log_debug("SIGINT CAPTURED (ctrl-C)", log_level);
		log_debug("EXIT WITH STATUS CODE 0", log_level);
		log_debug("(exit without message)", log_level);
		exit(0);
	}
}

// Exit minishell with message "exit" to STDOUT.
// The status code upon exit is 0.
int	exit_with_sigeof(void)
{
	t_loglevel	log_level;

	_loglevel_notice();
	log_level = LOG_QUIET;
	log_debug("EOF CAPTURED (ctrl-D)", log_level);
	log_debug("EXIT WITH STATUS CODE 0", log_level);
	log_info("exit", log_level);
	return (0);
}

// Show signal handler log_level notice.
static void	_loglevel_notice(void)
{
	t_loglevel	log_level;

	log_level = LOG_QUIET;
	log_debug("###################################################", log_level);
	log_debug("######### Signal handler log_level warning ########", log_level);
	log_debug("###################################################", log_level);
	log_debug("Signal handler log_levels are configured separately", log_level);
	log_debug("from the common configuration. The signal handler", log_level);
	log_debug("log_levels are controllable from", log_level);
	log_debug("utils/ft_sig_handler.c", log_level);
	log_debug("###################################################", log_level);
}
