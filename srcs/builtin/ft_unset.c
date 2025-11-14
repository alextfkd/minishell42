/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:30:30 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/15 02:41:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_app *app, t_cmd *cmd)
{
	(void)app;
	printf("unset %s\n", cmd->argv[0]);
	return (0);
}

/**
 * @brief
 *
 * @param env_list
 * @param key
 * @return int
 */
int	unset_key_from_env_list(t_env **env_list, const char *key)
{
	(void)env_list;
	(void)key;
	return (0);
}
