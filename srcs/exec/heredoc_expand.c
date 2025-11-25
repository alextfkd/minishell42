/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 17:03:44 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_get_value_after_doller(t_app *app, char *str, int *i);
static char	*_get_dollar_expansion(t_app *app, char *line, int *i);

/**
 * @brief Performs environment variable expansion on a single line of heredoc
 * input.This function iterates through the line, finds '$' characters,
 * and replaces variable names (like $VAR) or the exit status ($?) with their
 * corresponding values. and Free the memory allocated to the variable line..
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
	if (!line)
		return (new_line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			tmp_value = _get_dollar_expansion(app, line, &i);
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
	free(line);
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

/**
 * @briefHandles the expansion of '$' logic within a heredoc.
 * Checks for exit status ($?), environment variables, or literal '$'.
 * Updates the index 'i' accordingly.
 *
 * @param app
 * @param line
 * @param i
 * @return char*
 */
static char	*_get_dollar_expansion(t_app *app, char *line, int *i)
{
	char	*val;

	(*i)++;
	if (line[*i] == '?')
	{
		val = ft_itoa(app->shell->status);
		(*i)++;
	}
	else if (is_env_char(line[*i], FIRST_CHAR))
		val = _get_value_after_doller(app, line, i);
	else
		val = ft_strdup("$");
	return (val);
}
