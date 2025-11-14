/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:44:03 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/15 04:45:58 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_is_validate_args(const char *args);
static int	_is_env_char(char c, int mode);

/**
 * @brief Register the arrguments with the export attribute,
 * and set the values as environment variables and enviroment list.
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_export(t_app *app, t_cmd *cmd)
{
	int			i;
	int			update;
	const char	*args;

	if (!app || !cmd)
		return (1);
	if (cmd->argc < 2)
		return (print_env_attrib(app->env_list));
	update = 0;
	i = 1;
	while (i < cmd->argc)
	{
		args = cmd->argv[i];
		if (!_is_validate_args(args))
			printf("minishell: export `%s`: not a valid identifier\n", args);
		else
		{
			append_args_to_env_list(args, &app->env_list);
			update++;
		}
		i++;
	}
	if (update > 0)
		app->envp = rebuild_envp(app->env_list, app->envp);
	return (0);
}

/**
 * @brief Parses the input argument string and appends the resulting
 * environment node to the end of the environment linked list.
 *
 * This function uses 'get_env_from_env_line' to handle all parsing,
 *  memory allocation,and error checking (key/value extraction,
 *  is_set flag setting).
 *
 * @param args
 * @param env_list
 * @return int
 */
int	append_args_to_env_list(const char *args, t_env **env_list)
{
	t_env	*new_node;
	t_env	*current;

	new_node = get_env_from_env_line(args);
	if (!new_node)
		return (perror("minishell:create env_node failed"), 1);
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(new_node->key, current->key) == 0)
			return (overwrite_and_free_node(current, new_node), 0);
		current = current->next;
	}
	env_list_add_back(env_list, new_node);
	return (0);
}

/**
 * @brief Overwrites the existing environment node's value and is_set flag
 * with the new node's information, then safely frees the new node's remnants.
 *
 *  This function handles memory ownership transfer for 'value' to prevent
 * double freeing or memory leaks.
 *
 * @param current
 * @param new_node
 */
void	overwrite_and_free_node(t_env *current, t_env *new_node)
{
	if (current->value)
		free(current->value);
	if (new_node->is_set == ENV_SET)
	{
		current->value = new_node->value;
		current->is_set = ENV_SET;
	}
	else
	{
		current->is_set = ENV_UNSET;
		current->value = NULL;
		if (new_node->value)
			free(new_node->value);
	}
	free_env_node(new_node);
}

/**
 * @brief Validates if the argument string forms a valid environment variable
 * name.It extracts the key part (before the first '=') and checks if it
 * adheres to shell variable naming rules: the first character must be a letter
 * or underscore, and subsequent characters must be alphanumeric or
 * an underscore.
 *
 * @param args
 * @return int
 */
static int	_is_validate_args(const char *args)
{
	size_t		i;
	size_t		key_len;
	const char	*equal_pos;
	int			mode;

	if (args[0] == '\0')
		return (0);
	equal_pos = ft_strchr(args, '=');
	if (equal_pos == NULL)
		key_len = ft_strlen(args);
	else
		key_len = equal_pos - args;
	if (key_len == 0)
		return (0);
	i = 0;
	mode = FIRST_CHAR;
	while (i < key_len)
	{
		if (i != 0)
			mode = OTHER_CHAR;
		if (!_is_env_char(args[i], mode))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if a character is valid for an environment variable key based
 * on its position.
 *
 * @param c
 * @param mode Determines the character position (FIRST_CHAR or OTHER_CHAR)
 * @return int
 */
static int	_is_env_char(char c, int mode)
{
	if (mode == FIRST_CHAR)
		return (ft_isalpha(c) || c == '_');
	else
		return (ft_isdigit(c) || ft_isalpha(c) || c == '_');
}
