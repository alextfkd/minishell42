/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 02:36:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/14 17:55:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void _print_envp(char **envp);

/**
 * @brief Prints all environment variables to standard output
 *
 * @param app Pointer to the application context containing the environment.
 * @return 0 on success. 1 if the enviroment is not available.
 *
 */
int	ft_env(t_app *app)
{
	if (!app || !app->envp)
		return (1);
	_print_envp(app->envp);
	return (0);
}

static void _print_envp(char **envp)
{
	size_t i;
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
