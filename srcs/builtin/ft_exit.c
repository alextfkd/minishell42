/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/25 08:38:50 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exit test func,we have to program it correctly.
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_exit(t_app *app, t_cmd *cmd)
{
	(void)cmd;
	ft_putendl_fd("exit", 1);
	reset_stdio(app);
	free_tokens(app->token_head);
	free_list(&(app->cmd_list));
	free_shell(app->shell);
	exit(0);
}
