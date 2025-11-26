/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:44:03 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/26 16:23:54 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_register_export_args(t_app *app, t_cmd *cmd, int *update);

/**
 * @brief Register the arguments with the export attribute,
 * and set the values as environment variables and enviroment list.
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_export(t_app *app, t_cmd *cmd)
{
	int	ret;
	int	update;

	update = 0;
	if (!app || !cmd)
		return (1);
	if (cmd->argc < 2)
		return (print_env_attrib(app->env_list));
	ret = _register_export_args(app, cmd, &update);
	if (update > 0 && handle_update_env(app) != 0)
		return (1);
	return (ret);
}

/**
 * @brief Parse and register valid export arguments
 * into the environment list.
 *
 * @param app
 * @param cmd
 * @param update
 * @return int
 */
static int	_register_export_args(t_app *app, t_cmd *cmd, int *update)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (i < cmd->argc)
	{
		if (!is_validate_args(cmd->argv[i]))
		{
			print_builtin_cmd_error(cmd, i, "not a valid identifier", 1);
			ret = 1;
		}
		else
		{
			append_args_to_env_list(cmd->argv[i], &app->env_list);
			(*update)++;
		}
		i++;
	}
	return (ret);
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

	new_node = get_env_from_env_line(args);
	if (!new_node)
		return (perror("minishell: create env_node failed"), 1);
	return (add_or_update_env_node(env_list, new_node));
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
int	is_validate_args(const char *args)
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
		if (!is_env_char(args[i], mode))
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
int	is_env_char(char c, int mode)
{
	if (mode == FIRST_CHAR)
		return (ft_isalpha(c) || c == '_');
	else
		return (ft_isdigit(c) || ft_isalpha(c) || c == '_');
}
