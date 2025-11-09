/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:43:59 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 18:44:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin command
char	*ft_get_current_dir(void);
int		ft_pwd(void);
int		ft_env(t_app *app);
int		ft_unset(t_app *app, t_cmd *cmd);
int		ft_unset(t_app *app, t_cmd *cmd);
