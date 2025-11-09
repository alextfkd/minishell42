/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:30:30 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 20:32:54 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// delete valiables of key
int	env_unset_variable(t_env **env_list, const char *key)
{
	(void)env_list;
	(void)key;
	return (0);
}

int	ft_unset(t_app *app, t_cmd *cmd)
{
	(void)app;
	printf("unset %s\n", cmd->argv[0]);
	return (0);
}
