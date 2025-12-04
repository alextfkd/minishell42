/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:55:06 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/12/04 22:48:33 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "types.h"

static char	*_create_empty_str(char *s);
static char	*_remove_quote(char *s, t_ltstate initial_state);

int	rm_quote_overwrite(char **argv_i)
{
	char	*tmp;

	if (argv_i == NULL || *argv_i == NULL)
		return (1);
	tmp = rm_quote_strdup(*argv_i);
	if (tmp == NULL)
		return (1);
	free(*argv_i);
	*argv_i = tmp;
	return (0);
}

char	*rm_quote_strdup(char *s)
{
	char	*s_quote_removed;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (s[0] == '\'' && s[len] == '\'')
		s_quote_removed = _remove_quote(s, LT_SQUOTE);
	else if (s[0] == '\"' && s[len] == '\"')
		s_quote_removed = _remove_quote(s, LT_DQUOTE);
	else
		s_quote_removed = _remove_quote(s, LT_NORMAL);
	if (s_quote_removed == NULL)
		return (NULL);
	return (s_quote_removed);
}

static char	*_remove_quote(char *s, t_ltstate initial_state)
{
	t_ltstate	state;
	char		*out;
	char		*pout;

	out = _create_empty_str(s);
	if (!out)
		return (NULL);
	pout = out;
	state = initial_state;
	while (*s != '\0')
	{
		if (*s == '\'' && state == LT_NORMAL)
			state = LT_SQUOTE;
		else if ((*s == '\'' && state == LT_SQUOTE)
			|| (*s == '\"' && state == LT_DQUOTE))
			state = LT_NORMAL;
		else if (*s == '\"' && state == LT_NORMAL)
			state = LT_DQUOTE;
		else
			*pout++ = *s;
		s++;
	}
	*pout = '\0';
	return (out);
}

static char	*_create_empty_str(char *s)
{
	char		*out;

	if (!s)
		return (NULL);
	out = (char *)calloc(ft_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	return (out);
}
