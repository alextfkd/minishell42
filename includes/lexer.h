/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/28 00:25:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token	t_token;

// Quote status
typedef enum e_state
{
	S_NORMAL,
	S_DQUOTE,
	S_SQUOTE
}	t_state;

// Token kind
typedef enum e_tokenkind
{
	TK_INIT,
	TK_CHAR,
	TK_PIPE,
	TK_SEMI,
	TK_REDI_OUT_TRUC,
	TK_REDI_OUT_APPEND,
	TK_REDI_IN_FILE,
	TK_REDI_IN_HEREDOC
}	t_tokenkind;

typedef struct s_lexer
{
	char		*buf;
	int			idx;
	t_state		state;
	t_token		*head;
	t_token		*tail;
}	t_lexer;

//  Decomposed into token kind and value only
typedef struct s_token
{
	t_tokenkind		tk;
	char			*val;
	struct s_token	*next;
}	t_token;

int		extract_symbol_token(t_lexer *lex);
int		extract_word_token(t_lexer *lex);
t_token	*upsert_token(t_lexer *lex, t_tokenkind tk, char *start, int len);
t_token	*tokenize(char *input);
void	free_tokens(t_token *head);

#endif
