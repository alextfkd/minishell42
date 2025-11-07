/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:26:50 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 13:34:20 by htsutsum         ###   ########.fr       */
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

t_token	*upsert_token(t_lexer *lex, t_tkind tk, char *start, int len)
{
	char	*data;
	t_token	*new_token;

	data = malloc((len + 1) * sizeof(char));
	if (!data)
		return (NULL);
	ft_strlcpy(data, start, len + 1);
	data[len] = '\0';
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(data);
		return (NULL);
	}
	new_token->tk = tk;
	new_token->data = data;
	new_token->next = NULL;
	_append_token_to_list(lex, new_token);
	return (new_token);
}

t_token	*tokenize(char *input)
{
	t_lexer	lex;

	ft_bzero(&lex, sizeof(t_lexer));
	lex.line = input;
	while (lex.line[lex.idx] != '\0')
	{
		if (ft_isspace(lex.line[lex.idx]))
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
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
}
