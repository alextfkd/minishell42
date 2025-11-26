/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 02:39:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"

t_token	*tokenize(char *input, int *status);

t_token	*create_new_token(t_lexer *lex, t_tkind tk, int start, int end);
void	free_tokens(t_token *head);

t_token	*extract_symbol_token(t_lexer *lex);
t_token	*extract_word_token(t_lexer *lex);

#endif
