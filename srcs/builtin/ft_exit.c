/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/17 12:54:36 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	if (kill(0, SIGINT) == -1)
	{
		perror("minishell: kill SIGINT error");
		exit(1);
	}
	exit(0);
}
