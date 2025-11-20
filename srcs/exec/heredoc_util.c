/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 00:16:10 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_get_value_after_doller(t_app *app, char *str, int *i);

/**
 * @brief Performs environment variable expansion on a single line of heredoc
 * input.This function iterates through the line, finds '$' characters,
 * and replaces variable names (like $VAR) or the exit status ($?) with their
 * corresponding values.
 *
 * @param line
 * @param app
 * @return char*
 */
char	*expand_heredoc_line(char *line, t_app *app)
{
	char	*new_line;
	char	*tmp_value;
	char	*old_line;
	int		i;

	new_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				tmp_value = ft_itoa(app->exit_status);
				i++;
			}
			else if (is_env_char(line[i], FIRST_CHAR))
				tmp_value = _get_value_after_doller(app, line, &i);
			else
				tmp_value = ft_strdup("$");
		}
		else
		{
			tmp_value = ft_substr(line, i, 1);
			i++;
		}
		old_line = new_line;
		new_line = ft_strjoin(old_line, tmp_value);
		free(old_line);
		free(tmp_value);
	}
	return (new_line);
}

/**
 * @brief Extracts an environment variable key from a string starting
 * immediately after a '$' and retrieves its corresponding value.
 * * This function stops reading the key when it hits a non-variable
 * character.
 *
 * @param app
 * @param str The full input line containing the variable starting
 *  at index '*i'.
 * @param i
 * @return char* A newly allocated string containing the environment
 * variable's value, or an empty string "" if the variable is not
 * found. Returns NULL on allocation failure.
 */
static char	*_get_value_after_doller(t_app *app, char *str, int *i)
{
	int		start;
	char	*key;
	char	*env_val;
	char	*result;

	if (!str)
		return (ft_strdup(""));
	start = *i;
	while (str[*i] && is_env_char(str[*i], OTHER_CHAR))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	env_val = get_env_value(app->env_list, key);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	free(key);
	return (result);
}
