/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/07 05:32:46 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_heredoc_ctrl_c_handler(int sig)
{
	(void)sig;
	exit(1);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = _heredoc_ctrl_c_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("minishell: sigaction SIGINT error");
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("minishell: sigaction SIGQUIT error");
}
