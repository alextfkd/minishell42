/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/20 19:58:01 by htsutsum         ###   ########.fr       */
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
	(void)app;
	(void)cmd;
	printf("buitin exit\n");
	if (kill(0, SIGINT) == -1)
	{
		perror("minishell: kill SIGINT error");
		exit(1);
	}
	return(0);
}
