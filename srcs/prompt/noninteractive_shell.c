/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:38 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 18:55:37 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_interactive_shell(
	t_shell *shell,
	char **envp
)
{
	log_debug("MINISHELL NON-INTERACTIVE MODE", shell->loglevel);
	execute_cmd(shell->argv[1], envp, shell->loglevel);
	return (0);
}
//log_debug_show_input(argv[1], log_level);
