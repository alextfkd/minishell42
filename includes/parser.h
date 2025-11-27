/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 02:00:58 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 02:39:58 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

// perser
t_astree			*create_astree_from_tokens(t_token **tokens_head,
						int *status);
int					append_red_to_cmd(t_cmd *cmd, t_token *current);
void				astree_add_branch(t_astree *root, t_astree *left,
						t_astree *right);
void				astree_clear(t_astree *node);
void				clear_cmd(t_cmd *cmd);
int					set_cmd_argv(t_cmd *cmd, t_token *start, t_token *end);
t_cmd				*tokens2cmd(t_token **tokens_head, int *status);
int					is_red(t_tkind tk);
t_red				*find_last_red(t_red *red);
void				red_add_back(t_red **head_red, t_red *new);
void				clear_red(t_red *head_red);

#endif
