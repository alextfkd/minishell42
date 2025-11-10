/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_symbol_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/10 06:05:48 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static t_token	*_extract_pipe_token(t_lexer *lex);
static t_token	*_extract_redirect_in_token(t_lexer *lex);
static t_token	*_extract_redirect_out_token(t_lexer *lex);

t_token	*extract_symbol_token(t_lexer *lex)
{
	t_token	*token;

	token = _extract_pipe_token(lex);
	if (token != NULL)
		return (token);
	token = _extract_redirect_in_token(lex);
	if (token != NULL)
		return (token);
	token = _extract_redirect_out_token(lex);
	if (token != NULL)
		return (token);
	return (NULL);
}

static t_token	*_extract_pipe_token(t_lexer *lex)
{
	t_token	*token;
	char	*word_start;
	int		idx;
	int		len;

	idx = lex->idx;
	word_start = lex->line + idx;
	len = 1;
	if (*word_start != '|')
		return (NULL);
	token = create_new_token(lex, TK_PIPE, idx, idx + len);
	if (token == NULL)
		return (NULL);
	lex->idx += len;
	return (token);
}

static t_token	*_extract_redirect_in_token(t_lexer *lex)
{
	t_token	*token;
	char	*word_start;
	int		idx;
	int		len;

	idx = lex->idx;
	word_start = lex->line + idx;
	if (*word_start == '<' && *(word_start + 1) == '<')
	{
		len = 2;
		token = create_new_token(lex, TK_RED_HEREDOC, idx, idx + len);
	}
	else if (*word_start == '<' && *(word_start + 1) != '<')
	{
		len = 1;
		token = create_new_token(lex, TK_RED_IN, idx, idx + len);
	}
	else
	{
		return (NULL);
	}
	if (token == NULL)
		return (NULL);
	lex->idx += len;
	return (token);
}

static t_token	*_extract_redirect_out_token(t_lexer *lex)
{
	t_token	*token;
	char	*word_start;
	int		idx;
	int		len;

	idx = lex->idx;
	word_start = lex->line + idx;
	if (*word_start == '>' && *(word_start + 1) == '>')
	{
		len = 2;
		token = create_new_token(lex, TK_RED_APPEND, idx, idx + len);
	}
	else if (*word_start == '>' && *(word_start + 1) != '>')
	{
		len = 1;
		token = create_new_token(lex, TK_RED_OUT, idx, idx + len);
	}
	else
	{
		return (NULL);
	}
	if (token == NULL)
		return (NULL);
	lex->idx += len;
	return (token);
}