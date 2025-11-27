/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 02:32:09 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 00:12:15 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

// log utils
void		log_debug(char *msg, t_loglevel log_level);
void		log_debug_show_input(char *msg, t_loglevel log_level);
void		log_warning(char *msg, t_loglevel log_level);
void		log_info(char *msg, t_loglevel log_level);
void		log_debug_show_token(t_token *token_head, t_loglevel log_level);
void		log_debug_show_ast(t_astree *ast_root, t_loglevel log_level);
void		log_debug_ms_buf(t_shell *shell);
void		print_redirections(t_red *red);

// app utils
void		free_app(t_app *app);
t_app		*setup_app(char **envp, t_shell *shell);
void		reset_stdio(t_app *app);

// env utils
t_env		*envp_to_env_list(char **envp);
char		**env_list_to_envp(t_env *env_list);
int			handle_update_env(t_app *app);
char		*get_key_env_line(const char *envp_line);
char		*get_value_env_line(const char *envp_line);
t_env		*get_env_from_env_line(const char *env_line);
char		**dup_env(char **main_envp);
char		*get_env_value(t_env *env_list, const char *key);
int			set_env_value(t_env **env_list, const char *key, const char *value);
int			add_or_update_env_node(t_env **env_list, t_env *new_node);
void		free_env_node(t_env *node);
void		*free_env_vars(char *key, char *value);
void		free_envp(char **envp, size_t size);

// env list util
void		free_env_list(t_env *env_list);
t_env		*env_new_node(char *key, char *value, int is_set);
size_t		env_list_size(t_env *env_list, int mode);
void		env_list_add_back(t_env **env_list, t_env *new_node);
t_env		*env_last_list(t_env *env_list);
t_astree	*astree_create_cmd_node(t_token **tokens_head, int *status);
t_astree	*astree_create_pipe_node(t_astree *left, t_astree *right,
				int *status);

// builtin util
char		*get_current_dir(t_app *app);
void		print_builtin_error(t_cmd *cmd, int i, const char *msg,
				int quate_flag);

#endif
