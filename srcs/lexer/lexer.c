/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:26:50 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/28 01:12:03 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_append_token_to_list(t_lexer *lex, t_token *new_token)
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

t_token	*upsert_token(t_lexer *lex, t_tokenkind tk, char *start, int len)
{
	char	*val;
	t_token	*new_token;

	val = malloc((len + 1) * sizeof(char));
	if (!val)
		return (NULL);
	ft_strlcpy(val, start, len + 1);
	val[len] = '\0';
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(val);
		return (NULL);
	}
	new_token->tk = tk;
	new_token->val = val;
	new_token->next = NULL;
	_append_token_to_list(lex, new_token);
	return (new_token);
}

t_token	*tokenize(char *input)
{
	t_lexer	lex;

	ft_bzero(&lex, sizeof(t_lexer));
	lex.buf = input;
	while (lex.buf[lex.idx] != '\0')
	{
		if (ft_isspace(lex.buf[lex.idx]))
			lex.idx++;
		else if (extract_symbol_token(&lex) == 0)
			;
		else if (extract_word_token(&lex) == 0)
			;
		else
		{
			free_tokens(lex.head);
			return (NULL);
		}
	}
	if (lex.state != S_NORMAL)
	{
		log_debug("minishell: syntax error: unclosed quote", LOG_DEBUG);
		free_tokens(lex.head);
		return (NULL);
	}
	return (lex.head);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->val)
			free(tmp->val);
		free(tmp);
	}
}
