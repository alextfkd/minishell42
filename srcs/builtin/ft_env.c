/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 02:36:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/04 02:39:27 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_print_envp(char **envp, t_loglevel loglevel);

/**
 * @brief Prints all environment variables to standard output
 *
 * @param app Pointer to the application context containing the environment.
 * @return 0 on success. 1 if the enviroment is not available.
 *
 */
int	ft_env(t_app *app, t_cmd *cmd)
{
	(void)cmd;
	log_debug("ft_env()", app->shell->loglevel);
	if (!app || !app->envp)
		return (1);
	_print_envp(app->envp, app->shell->loglevel);
	return (0);
}

static void	_print_envp(char **envp, t_loglevel loglevel)
{
	size_t	i;

	i = 0;
	log_debug("_print_envp()", loglevel);
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
