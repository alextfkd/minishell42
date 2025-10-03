/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:08:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/03 16:56:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_getc_fd(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*bufp;
	static ssize_t	n;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
		{
			n = 0;
			return (READ_ERROR);
		}
		bufp = buf;
	}
	if (--n >= 0)
	{
		return ((unsigned char)*bufp++);
	}
	n = 0;
	return (EOF);
}

static int	push_stack(t_line *line, char c)
{
	size_t	i;
	char	*tmp;

	if (line->len + 1 > line->capa)
	{
		tmp = line->str;
		line->str = (char *)malloc((line->capa + EXTEND_SIZE) * sizeof(char));
		if (!line->str)
		{
			free(tmp);
			return (1);
		}
		i = 0;
		while (i < line->len)
		{
			line->str[i] = tmp[i];
			i++;
		}
		free(tmp);
		line->capa += EXTEND_SIZE;
	}
	line->str[line->len] = c;
	line->len++;
	return (0);
}

char	*get_next_line(int fd)
{
	t_line	line;
	int		c;

	line.str = NULL;
	line.len = 0;
	line.capa = 0;
	while (1)
	{
		c = ft_getc_fd(fd);
		if (c == READ_ERROR)
			return (free(line.str), NULL);
		if (c == EOF)
			break ;
		if (push_stack(&line, c))
			return (NULL);
		if (c == '\n')
			break ;
	}
	if (line.len > 0)
		if (push_stack(&line, '\0'))
			return (NULL);
	return (line.str);
}
