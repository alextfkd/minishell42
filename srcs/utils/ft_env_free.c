/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:06:08 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 00:14:44 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief free the minishell enviroment variables.
 *
 * @param envp
 * @param size
 *
 * */
void	free_envp(char **envp, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (envp[i])
			free(envp[i]);
		i++;
	}
	free(envp);
}

/**
 * @brief free key and value variables
 *
 * @param key
 * @param value
 * @return void*
 */
void	*free_env_vars(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	return (NULL);
}
