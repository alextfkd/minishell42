/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:38 by marvin            #+#    #+#             */
/*   Updated: 2025/10/31 22:12:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_interactive_shell(t_shell *shell, char **envp)
{
	t_app	app;

	log_debug("MINISHELL NON-INTERACTIVE MODE", shell->loglevel);
	setup_app(&app, envp);
	execute_cmd(shell->argv[1], &app, shell->loglevel);
	clear_app(&app);
	return (0);
}
