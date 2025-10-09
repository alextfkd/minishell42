/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:13:40 by tkatsumata        #+#    #+#             */
/*   Updated: 2025/10/09 09:52:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#define FT_PROMPT "> "

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		printf("SIGINT CAPTURED (ctrl-C)\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	char *input;

	(void)argc;
	(void)argv;
	input = NULL;
	while (1)
	{
		input = readline(FT_PROMPT);
		printf("\n\ntmp -> %s\n", input);
		signal(SIGINT, sighandler);
	}
	return (0);
}
