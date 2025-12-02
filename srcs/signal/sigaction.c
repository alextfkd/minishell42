/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 08:55:19 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/30 21:21:53 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERR_MSG "Failed to set sigaction."

/**
 * @brief Set the sigaction handlers.
 * SIGINT will be handled by sigint_handler().
 * SIGQUIT will be handled by sigquit_handler().
 *
 * @param shell
 * @return int
 *
 * Returns 0 on success.
 * Returns 1 and set shell->status value to 1 if sigaction failed.
 */
int	set_sigaction(t_shell *shell)
{
	struct sigaction	sa;

	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(ERR_MSG);
		shell->status = 1;
		return (1);
	}
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = sigquit_handler;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror(ERR_MSG);
		shell->status = 1;
		return (1);
	}
	signal(SIGTSTP, SIG_IGN);
	return (0);
}
