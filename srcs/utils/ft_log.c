/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 02:43:41 by marvin            #+#    #+#             */
/*   Updated: 2025/10/16 01:52:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print log message to STDOUT if log_level <= LOG_DEBUG.
void	log_debug(char *msg, t_loglevel log_level)
{
	if (log_level <= LOG_DEBUG)
		printf("[DEBUG]   %s\n", msg);
}

// Print log message to STDOUT if log_level <= LOG_DEBUG.
// Use this function to visualize the user input.
void	log_debug_show_input(char *input, t_loglevel log_level)
{
	if (log_level <= LOG_DEBUG)
		printf("[DEBUG]   input -> %s\n", input);
}

// Print log message to STDOUT if log_level <= LOG_WARNING.
void	log_warning(char *msg, t_loglevel log_level)
{
	if (log_level <= LOG_WARNING)
		printf("[WARNING] %s\n", msg);
}

// Print log message to STDOUT if log_level <= LOG_QUIET.
// If log_level <= LOG_INFO, the output will be "[INFO] (msg)" style.
// If log_level == LOG_QUIET, the output will be "msg" style.
void	log_info(char *msg, t_loglevel log_level)
{
	if (log_level <= LOG_INFO)
		printf("[INFO]    %s\n", msg);
	if (log_level <= LOG_QUIET)
		printf("%s\n", msg);
}
