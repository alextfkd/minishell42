/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/10 20:29:16 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	_is_break_point(char c);
static int	_update_quote_state(t_lexer *lex, char c);
//static int	_handle_char_and_quote_state(t_lexer *lex, char c);

t_token	*extract_word_token(t_lexer *lex)
{
	char	c;
	int		start;
	int		idx;
	t_token	*token;

	start = lex->idx;
	idx = start;
	while (lex->line[idx] != '\0' || lex->state != S_NORMAL)
	{
		c = lex->line[idx];
		_update_quote_state(lex, c);
		if (_is_break_point(c) && lex->state == S_NORMAL)
			break ;
		if (c == '\0')
			break ;
		idx++;
	}
	if (start == idx)
		return (NULL);
	lex->idx = idx;
	token = create_new_token(lex, TK_CHAR, start, idx);
	if (!token)
		return (NULL);
	return (token);
}

/* Returns 1 if c is a character break point (isspace(), |<>;\0) */
static int	_is_break_point(char c)
{
	if (ft_isspace(c) || ft_strchr("|<>", c) || c == ';' || c == '\0')
		return (1);
	return (0);
}

static int	_update_quote_state(t_lexer *lex, char c)
{
	if (lex == NULL)
		return (1);
	if (lex->state == S_NORMAL && c == '\'')
		lex->state = S_SQUOTE;
	else if (lex->state == S_NORMAL && c == '\"')
		lex->state = S_DQUOTE;
	else if (lex->state == S_SQUOTE && c == '\'')
		lex->state = S_NORMAL;
	else if (lex->state == S_DQUOTE && c == '\"')
		lex->state = S_NORMAL;
	return (0);
}

/*
static int	_handle_char_and_quote_state(t_lexer *lex, char c)
{
	if (c == '\0')
		return (1);
	if (lex->state == S_NORMAL && _is_char_break_point(c))
		return (1);
	if (lex->state == S_NORMAL && c == '\'')
	{
		lex->state = S_SQUOTE;
		return (0);
	}
	if (lex->state == S_NORMAL && c == '\"')
	{
		lex->state = S_DQUOTE;
		return (0);
	}
	if (lex->state == S_SQUOTE && c == '\'')
	{
		lex->state = S_NORMAL;
	}
	if (lex->state == S_DQUOTE && c == '\"')
	{
		lex->state = S_NORMAL;
	}
	return (0);
}
*/