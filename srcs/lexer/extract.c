/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:17 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 11:25:50 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	_extract_pipe_token(t_lexer *lex)
{
	char	*start;
	int		len;

	start = lex->buf + lex->idx;
	if (*start != '|')
		return (1);
	len = 1;
	if (upsert_token(lex, TK_PIPE, start, len) == NULL)
		return (1);
	lex->idx += len;
	return (0);
}

static int	_extract_redirin_token(t_lexer *lex)
{
	char		*start;
	t_tokenkind	tk;
	int			len;

	start = lex->buf + lex->idx;
	if (*start != '<')
		return (1);
	if (*(start + 1) == '<')
	{
		tk = TK_REDI_HEREDOC;
		len = 2;
	}
	else
	{
		tk = TK_REDI_IN;
		len = 1;
	}
	if (upsert_token(lex, tk, start, len) == NULL)
		return (1);
	lex->idx += len;
	return (0);
}

static int	_extract_redirout_token(t_lexer *lex)
{
	char		*start;
	t_tokenkind	tk;
	int			len;

	start = lex->buf + lex->idx;
	if (*start != '>')
		return (1);
	if (*(start + 1) == '>')
	{
		tk = TK_REDI_APPEND;
		len = 2;
	}
	else
	{
		tk = TK_REDI_OUT;
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
	if (_extract_redirin_token(lex) == 0)
		return (0);
	if (_extract_redirout_token(lex) == 0)
		return (0);
	return (1);
}

int	extract_char_token(t_lexer *lex)
{
	char	c;
	char	*start;
	int		start_idx;
	int		len;

	start_idx = lex->idx;
	start = lex->buf + start_idx;
	while (lex->buf[lex->idx])
	{
		c = lex->buf[lex->idx];
		if (ft_isspace(c) || ft_strchr("|<>", c))
			break ;
		lex->idx++;
	}
	len = lex->idx - start_idx;
	if (len > 0)
	{
		if (upsert_token(lex, TK_CHAR, start, len) == NULL)
			return (1);
		return (0);
	}
	return (1);
}
