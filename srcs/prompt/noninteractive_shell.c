/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:38 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 15:29:52 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_interactive_shell(t_shell *shell)
{
	log_debug("MINISHELL NON-INTERACTIVE MODE", shell->loglevel);
	pipeline_executor(shell);
	return (0);
}
