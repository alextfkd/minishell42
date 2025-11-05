/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 08:32:03 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reterievs the current working directory as allocated string.
 *
 * @return char* Pointer to the current working string,or NULL on error.
 */
char	*ft_get_current_dir(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
	{
		perror("minishell: getcwd error");
		return (NULL);
	}
	return (strdup(path));
}

/**
 * @brief Prints the current sworking directory
 *
 * @return int 0 if successful,1 on error.
 */
int	ft_pwd(void)
{
	char	*path;

	path = ft_get_current_dir();
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
