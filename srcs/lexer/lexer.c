/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:26:50 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/11 07:44:53 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*_tokenize(t_lexer *lex);
static void	_extend_lexer_tokens(t_lexer *lex, t_token *new_token);

t_token	*tokenize(char *input)
{
	t_lexer	lex;
	t_token	*token;

	ft_bzero(&lex, sizeof(t_lexer));
	lex.line = input;
	while (lex.line[lex.idx] != '\0')
	{
		if (ft_isspace(lex.line[lex.idx]))
		{
			lex.idx++;
			continue ;
		}
		token = _tokenize(&lex);
		if (token == NULL)
			return (free_tokens(lex.head), NULL);
		_extend_lexer_tokens(&lex, token);
	}
	if (lex.state != S_NORMAL)
	{
		//log_debug("minishell: syntax error: unclosed quote", LOG_DEBUG);
		lex.head->state = lex.state;
		return (lex.head);
		//return (free_tokens(lex.head), NULL);
	}
	lex.head->state = lex.state;
	return (lex.head);
}

t_token	*_tokenize(t_lexer *lex)
{
	t_token	*new_token;

	new_token = extract_symbol_token(lex);
	if (new_token != NULL)
		return (new_token);
	new_token = extract_word_token(lex);
	if (new_token != NULL)
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
