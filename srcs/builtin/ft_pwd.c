/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/15 03:03:26 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the current working directory to standard output.
 *  as the buitin command "PWD"
 *
 * @return int 0 if successful,1 on error.
 */
int	ft_pwd(void)
{
	char	*path;

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
