/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:26:50 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/19 02:50:32 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		_is_empty_or_null(char *input);
static t_lexer	*_init_lex(char *input, int *status);
static t_token	*_tokenize(t_lexer *lex);
static void		_extend_lexer_tokens(t_lexer *lex, t_token *new_token);

t_token	*tokenize(char *input, int *status)
{
	t_lexer	*lex;
	t_token	*token;

	*status = 0;
	if (_is_empty_or_null(input))
		return (NULL);
	lex = _init_lex(input, status);
	while (lex->line[lex->idx] != '\0')
	{
		if (ft_isspace(lex->line[lex->idx]))
		{
			lex->idx++;
			continue ;
		}
		token = _tokenize(lex);
		if (token == NULL || lex->status != 0)
		{
			*status = 1;
			return (free_tokens(lex->head), NULL);
		}
		_extend_lexer_tokens(lex, token);
	}
	lex->head->state = lex->state;
	token = lex->head;
	return (free(lex), token);
}

static t_lexer	*_init_lex(char *input, int *status)
{
	t_lexer	*lex;

	lex = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (lex == NULL)
	{
		*status = 1;
		return (NULL);
	}
	lex->line = input;
	lex->state = S_NORMAL;
	lex->status = 0;
	return (lex);
}

static int	_is_empty_or_null(char *input)
{
	char	*p;

	if (input == NULL)
		return (1);
	p = input ;
	while (*p != '\0')
	{
		if (isspace(*p))
			p++;
		else
			return (0);
	}
	return (1);
}

static t_token	*_tokenize(t_lexer *lex)
{
	t_token	*new_token;

	new_token = extract_symbol_token(lex);
	if (new_token != NULL || lex->status != 0)
		return (new_token);
	new_token = extract_word_token(lex);
	if (new_token != NULL || lex->status != 0)
		return (new_token);
	return (NULL);
}

static void	_extend_lexer_tokens(t_lexer *lex, t_token *new_token)
{
	if (!lex->head)
	{
		lex->head = new_token;
		lex->tail = new_token;
	}
	else
	{
		lex->tail->next = new_token;
		lex->tail = new_token;
	}
}
