/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/19 02:14:17 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	_is_break_point(char c);
static int	_update_quote_state(t_lexer *lex, char c);

/**
 * @brief  Create a TK_CHAR token from lex->line.
 * 
 * @param lex 
 * @return t_token* 
 */
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
		if (c == '\\' && lex->line[idx + 1] == '\n' && lex->state == S_NORMAL)
			break ;
		if (_is_break_point(c) && lex->state == S_NORMAL)
			break ;
		idx++;
	}
	if (start == idx)
		return (NULL);
	lex->idx = idx;
	token = create_new_token(lex, TK_CHAR, start, idx);
	if (token == NULL)
		lex->status = 1;
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
