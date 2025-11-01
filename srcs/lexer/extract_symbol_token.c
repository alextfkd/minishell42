/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_symbol_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 10:29:58 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	_extract_pipe_token(t_lexer *lex)
{
	char	*start;
	int		len;

	start = lex->line + lex->idx;
	if (*start != '|')
		return (1);
	len = 1;
	if (upsert_token(lex, TK_PIPE, start, len) == NULL)
		return (1);
	lex->idx += len;
	return (0);
}

static int	_extract_redirect_in_token(t_lexer *lex)
{
	char		*start;
	t_tkind		tk;
	int			len;

	start = lex->line + lex->idx;
	if (*start != '<')
		return (1);
	if (*(start + 1) == '<')
	{
		tk = TK_RED_HEREDOC;
		len = 2;
	}
	else
	{
		tk = TK_RED_IN;
		len = 1;
	}
	if (upsert_token(lex, tk, start, len) == NULL)
		return (1);
	lex->idx += len;
	return (0);
}

static int	_extract_redirect_out_token(t_lexer *lex)
{
	char		*start;
	t_tkind		tk;
	int			len;

	start = lex->line + lex->idx;
	if (*start != '>')
		return (1);
	if (*(start + 1) == '>')
	{
		tk = TK_RED_APPEND;
		len = 2;
	}
	else
	{
		tk = TK_RED_OUT;
		len = 1;
	}
	if (upsert_token(lex, tk, start, len) == NULL)
		return (1);
	lex->idx += len;
	return (0);
}

int	extract_symbol_token(t_lexer *lex)
{
	if (_extract_pipe_token(lex) == 0)
		return (0);
	if (_extract_redirect_in_token(lex) == 0)
		return (0);
	if (_extract_redirect_out_token(lex) == 0)
		return (0);
	return (1);
}
