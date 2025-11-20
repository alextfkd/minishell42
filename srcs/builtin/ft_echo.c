/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:30:03 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/20 19:55:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief The empty cd func,we have to program it correctly
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_echo(t_app *app, t_cmd *cmd)
{
	(void)app;
	(void)cmd;
	printf("buitlin echo\n");
	return (0);
}
