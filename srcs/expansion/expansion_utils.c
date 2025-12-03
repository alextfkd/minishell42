/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 08:17:10 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/12/03 23:07:29 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_update_quote_state(char c, t_ltstate *state);

char	*expand_argv(char *argv, t_app *app)
{
	t_ltstate	state;
	char		*new;
	char		*tmp;
	int			i;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	state = LT_NORMAL;
	i = 0;
	while (argv[i])
	{
		_update_quote_state(argv[i], &state);
		if (argv[i] == '$' && state != LT_SQUOTE)
			tmp = get_dollar_expansion(app, argv, &i);
		else
		{
			tmp = ft_substr(argv, i, 1);
			i++;
		}
		new = join_and_free(new, tmp);
		if (!new)
			return (NULL);
	}
	return (new);
}

int	overwrite_argv(char **argv_i, char *new_argv)
{
	if (argv_i == NULL)
		return (1);
	if (*argv_i != NULL)
		free(*argv_i);
	*argv_i = new_argv;
	return (0);
}

/**
 * @brief State Transition of Quotes
 *
 * @param c
 * @param state
 */
static void	_update_quote_state(char c, t_ltstate *state)
{
	if (*state == LT_NORMAL)
	{
		if (c == '\'')
			*state = LT_SQUOTE;
		else if (c == '\"')
			*state = LT_DQUOTE;
	}
	else if (*state == LT_SQUOTE && c == '\'' )
		*state = LT_NORMAL;
	else if (*state == LT_DQUOTE && c == '\"')
		*state = LT_NORMAL;
}

int	is_ambiguous_redirect(char *file)
{
	t_ltstate	state;
	int			i;

	if (!file || *file == '\0')
		return (1);
	state = LT_NORMAL;
	i = 0;
	while (file[i])
	{
		_update_quote_state(file[i], &state);
		if (state == LT_NORMAL && (file[i] == ' ' || file[i] == '\t'))
			return (1);
		i++;
	}
	return (0);
}
