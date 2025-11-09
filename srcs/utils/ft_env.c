/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:09:56 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 18:34:56 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Combines a key and a value to create an environment variable string
 * in "KEY=VALUE\0" format.
 *
 * @param key
 * @param value
 * @return char
 *
**/
static char	*_format_to_envp(char *key, char *value)
{
	char	*line;
	size_t	len;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	len = key_len + value_len + 2;
	line = (char *)ft_calloc(sizeof(char), len);
	if (!line)
	{
		perror("minishell: format envp failed");
		return (NULL);
	}
	ft_memcpy(line, key, ft_strlen(key));
	line[key_len] = '=';
	ft_memcpy(line + key_len + 1, value, value_len);
	return (line);
}

/**
 * @brief Converts the standard envp into an internal enviroment list
 *
 * @param envp
 * @return t_env*
 */
t_env	*envp_to_env_list(char **envp)
{
	t_env	*new_node;
	t_env	*env_list;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		new_node = env_new_node(envp[i]);
		if (!new_node)
		{
			free_env_list(env_list);
			return (perror("minishell:create env_node failed"), NULL);
		}
		env_list_add_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

/**
 * @brief Creates the environment array (envp) from the environment
 * variable list.
 *
 * @param env_list
 * @return char**
*/
char	**env_list_to_envp(t_env *env_list)
{
	char	**envp;
	size_t	envp_size;
	t_env	*current;
	size_t	i;

	envp_size = env_list_size(env_list);
	envp = (char **)ft_calloc(envp_size + 1, sizeof(char *));
	if (!envp)
		return (perror("minishel:envp allocation failed"), NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		envp[i] = _format_to_envp(current->key, current->value);
		if (!envp[i])
		{
			perror("minishell:envp allocation failed");
			return (free_envp(envp, i), NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * @brief  Update the minshell array (envp) based on the enviroment list
 *
 * @param env_list
 * @param current_envp
 * @return char**
*/
char	**update_envp(t_env *env_list, char **current_envp)
{
	char	**new_envp;
	size_t	i;

	if (current_envp)
	{
		i = 0;
		while (current_envp[i])
		{
			if (current_envp[i])
				free(current_envp[i]);
			i++;
		}
	}
	free(current_envp);
	new_envp = env_list_to_envp(env_list);
	if (!new_envp)
	{
		perror("minishell: envp update failed");
		return (NULL);
	}
	return (new_envp);
}

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
