/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 02:36:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 09:05:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all environment variables to standard output
 *
 * @param app Pointer to the application context containing the environment.
 * @return 0 on success. 1 if the enviroment is not available.
 *
 */
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
