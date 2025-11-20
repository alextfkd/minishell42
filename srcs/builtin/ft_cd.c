 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:54:19 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/20 17:50:57 by htsutsum         ###   ########.fr       */
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
int	ft_cd(t_app *app, t_cmd *cmd)
{
	(void)app;
	(void)cmd;
	printf("cd\n");
	return(0);
}
