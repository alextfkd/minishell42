/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/30 10:29:18 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

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
int			extract_symbol_token(t_lexer *lex);
int			extract_word_token(t_lexer *lex);
t_token		*upsert_token(t_lexer *lex, t_tkind tk, char *start, int len);
t_token		*tokenize(char *input);
void		free_tokens(t_token *head);

// ast utils
t_astree	*create_ast_node(t_node type, t_cmd *cmd, t_astree *left, t_astree *right);
void		astree_add_branch(t_astree *root, t_astree *left, t_astree *right);
void		clear_astree(t_astree *node);

// redirection parser
void		clear_red(t_red *head_red);
t_red		*create_red_node(t_tkind tk, char *data);
int			handle_red(t_cmd *cmd, t_token **current);

#endif
