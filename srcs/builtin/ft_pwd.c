/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/14 17:48:55 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_get_current_dir(void);

/**
 * @brief Prints the current working directory to standard output.
 *  as the buitin command "PWD"
 *
 * @return int 0 if successful,1 on error.
 */
int	ft_pwd(void)
{
	char	*path;

	path = _get_current_dir();
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
static char	*_get_current_dir(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		return (perror("minishell: getcwd error"), NULL);
	return (strdup(path));
}
