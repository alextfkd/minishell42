/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:54:40 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/16 01:25:25 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*_create_new_token(t_tkind tk, char *data);

t_token	*create_new_token(t_lexer *lex, t_tkind tk, int start, int end)
{
	char	*word_start;
	int		len;
	char	*data;
	t_token	*new_token;

	word_start = lex->line + start;
	len = end - start;
	data = (char *)ft_calloc(1, (len + 1) * sizeof(char));
	if (!data)
		return (NULL);
	ft_strlcpy(data, word_start, len + 1);
	new_token = _create_new_token(tk, data);
	if (!new_token)
		return (free(data), NULL);
	return (new_token);
}

static t_token	*_create_new_token(t_tkind tk, char *data)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		return (NULL);
	}
	new_token->tk = tk;
	new_token->data = data;
	new_token->next = NULL;
	return (new_token);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->data)
		{
			free(tmp->data);
			tmp->data = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}
