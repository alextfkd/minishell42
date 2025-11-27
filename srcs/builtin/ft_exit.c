/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 13:50:59 by tkatsuma         ###   ########.fr       */
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
	ft_putendl_fd("EXIT", 1);
	exit_process(0, app);
	return (0);
}

void	exit_process(int status, t_app *app)
{
	reset_stdio(app);
	free_tokens(app->token_head);
	app->token_head = NULL;
	free_list(&(app->cmd_list));
	app->cmd_list = NULL;
	free_ms_buf(&app->shell->ms_buf);
	app->shell->ms_buf = NULL;
	free_shell(app->shell);
	exit(status);
}
