/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/17 21:48:56 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the current working directory to standard output.
 *  as the buitin command "PWD"
 *
 * @return int 0 if successful,1 on error.
 */
int	ft_pwd(t_app *app, t_cmd *cmd)
{
	char	*path;

	(void)app;
	(void)cmd;
	path = get_current_dir();
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}

/**
 * @brief Reterievs the current working directory as allocated string.
 *
 * @return char* Pointer to the current working string,or NULL on error.
 */
char	*get_current_dir(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		return (perror("minishell: getcwd error"), NULL);
	return (strdup(path));
}
