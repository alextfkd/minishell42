/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 20:30:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_residual_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
	{
		close(fd);
		fd++;
	}
}

