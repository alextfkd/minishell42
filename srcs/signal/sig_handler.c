/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:14:43 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 08:47:51 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle SIGINT (Ctrl + C) signal.
// This handler will put "^C\n" to the stdout, refresh readline buffer 
// and pass 0 to g_sig_received value.
void	sigint_handler(int signal)
{
	t_loglevel	log_level;

	log_level = LOG_QUIET;
	log_debug("SIGINT CAPTURED (ctrl-C)", log_level);
	if (signal == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig_received = 0;
	}
}

// Handle SIGQUIT (Ctrl + \) signal.
// This handler will ignore SIGQUIT and pass 0 to g_sig_received value.
void	sigquit_handler(int signal)
{
	t_loglevel	log_level;

	log_level = LOG_QUIET;
	log_debug("SIGQUIT CAPTURED (ctrl-\\)", log_level);
	if (signal == SIGQUIT)
	{
		g_sig_received = 0;
	}
}

// Exit minishell with message "exit" to STDOUT.
// The status code upon exit is 0.
int	exit_with_sigeof(void)
{
	t_loglevel	log_level;

	log_level = LOG_QUIET;
	g_sig_received = EOF;
	log_debug("EOF CAPTURED (ctrl-D)", log_level);
	log_info("exit", log_level);
	return (0);
}

/*
// Show signal handler log_level notice.
static void	_loglevel_notice(void)
{
	t_loglevel	log_level;

	log_level = LOG_DEBUG;
	log_debug("###################################################", log_level);
	log_debug("######### Signal handler log_level warning ########", log_level);
	log_debug("###################################################", log_level);
	log_debug("Signal handler log_levels are configured separately", log_level);
	log_debug("from the common configuration. The signal handler", log_level);
	log_debug("log_levels are controllable from", log_level);
	log_debug("utils/ft_sig_handler.c", log_level);
	log_debug("###################################################", log_level);
}
*/
