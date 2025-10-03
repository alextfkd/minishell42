/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:31 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/06/30 00:53:32 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SEP -1
#define NSEP 1

// Check if char c is in the splitter char *sep.
static int	is_sep(const char c, const char sep)
{
	if (c == sep)
	{
		return (SEP);
	}
	if (c == '\0')
	{
		return (SEP);
	}
	return (NSEP);
}

// Count words splitted by *sep.
static int	word_count(const char *str, const char sep)
{
	int			count;
	const char	*ptr;

	count = 0;
	ptr = str;
	if (str == NULL || *str == '\0')
		return (0);
	if (sep == '\0')
		return (1);
	while (*ptr != '\0')
	{
		if (is_sep(*ptr, sep) * is_sep(*(ptr + 1), sep) < 0)
		{
			if (is_sep(*ptr, sep) == NSEP)
				count++;
		}
		ptr++;
	}
	return (count);
}

static int	sub_split(char **array, const char *s, char c)
{
	int			arr_i;
	int			word_start;
	size_t		s_i;

	arr_i = 0;
	s_i = 0;
	word_start = -1;
	while (s_i <= ft_strlen(s))
	{
		if (is_sep(s[s_i], c) == SEP && (word_start != -1))
		{
			array[arr_i] = ft_substr(s, word_start, s_i - word_start);
			word_start = -1;
			if (array[arr_i++] == NULL)
				return (0);
		}
		else if (is_sep(s[s_i], c) != SEP && word_start == -1)
			word_start = s_i;
		s_i++;
	}
	array[arr_i] = 0;
	return (1);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
	return ;
}

char	**ft_split(const char *s, char c)
{
	char		**array;
	int			wc;
	int			flag;

	wc = word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (wc + 1));
	if (array == NULL)
		return (NULL);
	flag = sub_split(array, s, c);
	if (flag == 0)
	{
		free_array(array);
		return (NULL);
	}
	return (array);
}
/*
#include <string.h>
#include <stdio.h>
#include <assert.h> 

void    print_and_free(char **a)
{
    int        i;

    if (a != NULL)
    {
        i = 0;
        while (a[i] != NULL)
        {
            printf("  %s\n", a[i]);
            free(a[i++]);
        }
    }
    free(a);
    printf("  ---free completed---\n");
}

int    testmain_split(void)
{
    char    **a;

    a = ft_split("hello world", ' ');
    assert(!strcmp(a[0], "hello"));
    assert(!strcmp(a[1], "world"));
    print_and_free(a);

    a = ft_split("abcdaba", 'a');
    assert(!strcmp(a[0], "bcd"));
    assert(!strcmp(a[1], "b"));
    print_and_free(a);

    a = ft_split("abcdaba", '\0');
    assert(!strcmp(a[0], "abcdaba"));
    print_and_free(a);

    a = ft_split("", 'a');
    assert(a == NULL);
    print_and_free(a);

    a = ft_split(NULL, 'a');//error
    assert(a == NULL);
    print_and_free(a);

    a = ft_split("      ", ' ');
    assert(a == NULL);
    print_and_free(a);

    a = ft_split("\0aa\0bbb", '\0');
    assert(a == NULL);
    print_and_free(a);

    return (0);
}

int    main(void)
{
    testmain_split();

    system("leaks a.out");
    return (0);
}
#include <stdio.h>

int main(void)
{
	char **arr;
	arr = ft_split("hello!", ' ');
	printf("wc->%d", word_count("hello!", ' '));
	int i;
	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i++]);
	}
	if (arr[1] == NULL)
		printf("OK");
	if (arr[2] == NULL)
		printf("OK");
	if (arr[3] == NULL)
		printf("OK");
	if (arr[4] == NULL)
		printf("OK");
	return (0);
}
*/
