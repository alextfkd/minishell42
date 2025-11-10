/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/10 06:23:52 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

// Quote status
typedef enum e_state
{
	S_NORMAL,
	S_DQUOTE,
	S_SQUOTE
}	t_state;

// Token kind
typedef enum e_tkind
{
	TK_CHAR,
	TK_PIPE,
	TK_RED_OUT,
	TK_RED_APPEND,
	TK_RED_IN,
	TK_RED_HEREDOC
}	t_tkind;

//  Decomposed into token kind and value only
struct s_token
{
	t_tkind		tk;
	char		*data;
	t_token		*next;
};

struct s_lexer
{
	char		*line;
	int			idx;
	t_state		state;
	t_token		*head;
	t_token		*tail;
};

// lexer
t_token *extract_symbol_token(t_lexer *lex);
//int			extract_word_token(t_lexer *lex);
t_token	*extract_word_token(t_lexer *lex);
//t_token		*upsert_token(t_lexer *lex, t_tkind tk, char *start, int len);
int			upsert_token(t_lexer *lex, t_tkind tk, int start, int end);
void	extend_lexer_tokens(t_lexer *lex, t_token *new_token);
t_token		*tokenize(char *input);
t_token	*create_new_token(t_lexer *lex, t_tkind tk, int start, int end);
void		free_tokens(t_token *head);

#endif
