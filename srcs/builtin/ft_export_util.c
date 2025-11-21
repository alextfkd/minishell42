/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:44:03 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/21 22:07:07 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_sort_env_array(t_env **arr, int size);
static void	_print_attrib_one(t_env *env);

/**
 * @brief Display all items registered in teh export attribute,
 * when no arguments are provided to the exprot commands.
 * Free the array (do not destroy the line)
 *
 * Count the number of elements in the list.
 * Allocate a pointer array with malloc for the number of elements.
 * Copy the address of each node in the list into the array.
 * Sort the array contents based on key (using bubble sort here for simplicity)
 * Display the elements in sorted array order.
 *
 * @param env_list
 * @return int
 */
int	print_env_attrib(const t_env *env_list)
{
	t_env		**env_arr;
	int			size;
	int			i;
	const t_env	*current;

	if (!env_list)
		return (0);
	size = env_list_size((t_env *)env_list, ENV_ALL);
	env_arr = (t_env **)malloc(sizeof(t_env *) * size);
	if (!env_arr)
		return (1);
	i = 0;
	current = env_list;
	while (current)
	{
		env_arr[i] = (t_env *)current;
		current = current->next;
		i++;
	}
	_sort_env_array(env_arr, size);
	i = 0;
	while (i < size)
	{
		_print_attrib_one(env_arr[i]);
		i++;
	}
	free(env_arr);
	return (0);
}

static void	_print_attrib_one(t_env *env)
{
	char	*value;

	if (ft_strcmp(env->key, "_") == 0)
		return ;

	if (env->is_set == ENV_SET)
	{
		value = "";
		if (env->value)
			value = env->value;
		printf("declare -x %s=\"%s\"\n", env->key, value);
	}
	else
		printf("declare -x %s\n", env->key);
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

static void	_sort_env_array(t_env **arr, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
