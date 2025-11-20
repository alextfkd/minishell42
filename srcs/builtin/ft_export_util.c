/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:44:03 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/20 22:39:27 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display all items registered in teh export attribute,
 * when no arguments are provided to the exprot commands.
 *
 * @param env_list
 * @return int
 */
int	print_env_attrib(const t_env *env_list)
{
	char	*value;

	if (!env_list)
		return (1);
	while (env_list)
	{
		value = "";
		if (env_list->is_set == ENV_SET && ft_strcmp(env_list->key, "_") != 0)
		{
			if (env_list->value)
				value = env_list->value;
			printf("declare -x %s=\"%s\"\n", env_list->key, value);
		}
		else if (ft_strcmp(env_list->key, "_") != 0)
		{
			printf("declare -x %s\n", env_list->key);
		}
		env_list = env_list->next;
	}
	return (0);
}

/**
 * @brief Frees the memory allocated for a single environment variable node
 * (t_env).
 * * This function handles the safe deallocation of the dynamically allocated
 * strings for the key and the value, followed by the deallocation of the node
 * structure itself.
 *
 * @param node
 */
void	free_env_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}
