/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 10:30:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

// Character break point
static int	_is_char_break_point(char c)
{
	if (ft_isspace(c) || ft_strchr("|<>", c) || c == ';' || c == '\0')
		return (1);
	return (0);
}

static int	_handle_char_and_quote_state(t_lexer *lex, char c)
{
	if (lex->state == S_NORMAL)
	{
		if (c == '\'')
			lex->state = S_SQUOTE;
		else if (c == '\"')
			lex->state = S_DQUOTE;
		else if (_is_char_break_point(c))
			return (1);
	}
	else if (lex->state == S_SQUOTE)
	{
		if (c == '\'')
			lex->state = S_NORMAL;
		else if (c == '\0')
			return (1);
	}
	else if (lex->state == S_DQUOTE)
	{
		if (c == '\"')
			lex->state = S_NORMAL;
		else if (c == '\0')
			return (1);
	}
	return (0);
}

int	extract_word_token(t_lexer *lex)
{
	char	c;
	int		start_idx;
	int		len;

	start_idx = lex->idx;
	while (lex->line[lex->idx] != '\0' || lex->state != S_NORMAL)
	{
		c = lex->line[lex->idx];
		if (_handle_char_and_quote_state(lex, c))
			break ;
		if (c == '\0')
			break ;
		lex->idx++;
	}
	len = lex->idx - start_idx;
	if (len > 0)
	{
		if (upsert_token(lex, TK_CHAR, lex->line + start_idx, len) == NULL)
			return (1);
		return (0);
	}
	return (1);
}
