/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 02:36:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 02:51:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_app *app)
{
	int	i;

	if (!app->envp)
		return (1);
	i = 0;
	while (app->envp[i] != NULL)
	{
		printf("%s\n", app->envp[i]);
		i++;
	}
	return (0);
}
