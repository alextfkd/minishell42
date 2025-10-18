/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 11:08:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token			t_token;
typedef struct s_redirection	t_redirection;
typedef struct s_pipeline		t_pipeline;

// lexer status
typedef enum e_state
{
	S_NORMAL,
	S_DQUOTE,
	S_SQUOTE
}								t_state;

// Token kind
typedef enum e_tokenkind
{
	TK_CHAR,
	TK_PIPE,
	TK_REDI_IN,
	TK_REDI_OUT,
	TK_REDI_HEREDOC,
	TK_REDI_APPEND
}								t_tokenkind;

typedef struct s_lexer
{
	char						*buf;
	int							idx;
	t_state						state;
	t_token						*head;
	t_token						*tail;
}								t_lexer;

//  Decomposed into token kind and value only
typedef struct s_token
{
	t_tokenkind					tk;
	char						*val;
	struct s_token				*next;
}								t_token;

// Auxiliary structure of redirection
typedef struct s_redirection
{
	t_tokenkind					tk;
	char						*file;
	t_redirection				*next;
}								t_redirection;

// Single command Structure
typedef struct s_cmd
{
	int							ac;
	char						**av;
	char						**ep;
	t_redirection				*red;
}								t_cmd;

// The entire pipline
typedef struct s_pipeline
{
	t_cmd						*cmd;
	t_pipeline					*next;
}								t_pipeline;

int								extract_symbol_token(t_lexer *lex);
int								extract_char_token(t_lexer *lex);

t_token							*upsert_token(t_lexer *lex, t_tokenkind tk,
									char *start, int len);
t_token							*tokenize(char *input);
void							free_tokens(t_token *head);

#endif
