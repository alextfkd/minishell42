/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:49:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/21 05:54:53 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

volatile sig_atomic_t	g_sig_received = 0;

static int	ft_assert_str(char *input, char *expected)
{
	if (!input && !expected)
		return (1);
	if (!input || !expected)
		return (0);
	if (ft_strcmp(input, expected) !=0)
	{
		printf("test -> %s, expected -> %s", input, expected);
		return (0);
	}
	return (1);
}

int	test_single_cmd(char *input)
{
	t_astree	*astree;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	if (ft_assert_str(astree->cmd->argv[0], input))
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	astree_clear(astree);
	return (status);
}


int	main(void)
{
	int	status;

	status = 0;
	//status += test_single_cmd(NULL);
	status += test_single_cmd("/bin/ls");
	return (status);
}
	//test_single_cmd(NULL, 0);
	//test_single_cmd("", 0);
	//test_single_cmd("/bin/ls", 0);
	//test_single_cmd("'/bin/ls'", 0);

	/*
	printf("\ntest: cmd1 arg1\n");
	test_2cmd("cmd arg");
	test_2cmd("      cmd  arg");
	test_2cmd("cmd  arg ");
	test_2cmd("cmd arg");

	printf("\ntest: cmd1 arg1 | cmd2 arg2\n");
	test_2cmd1pipe("cmd1 arg1 | cmd2 arg2");
	test_2cmd1pipe("      cmd1 arg1 | cmd2 arg2     ");
	test_2cmd1pipe("cmd1 arg1| cmd2 arg2");
	test_2cmd1pipe("cmd1 arg1 |cmd2 arg2");
	test_2cmd1pipe("cmd1 arg1\t|\tcmd2 arg2");

	printf("\ntest: cmd1 arg1 | cmd2 arg2 | cmd3 arg3\n");
	test_3cmd2pipe("cmd1 arg1 | cmd2 arg2 | cmd3 arg3");

	printf("\ntest: (cmd1)\n");
	test_cat_parenthesis("(cat)");

	printf("\ntest: \' cmd \'\n");
	test_cat_single_quote("\' cat \'");

	printf("\ntest: \'\'\n");
	test_single_quoted_empty("\'\'");
	test_single_quoted_empty("  \'\' ");

	printf("\ntest: \"\"\n");
	test_double_quoted_empty("\"\"");
	test_double_quoted_empty("  \"\" ");

	printf("\ntest: unclosed single quotes\n");
	test_unclosed_single_quote("cat 'Makefile");
	test_unclosed_single_quote("cat 'Makefile          ");
	test_unclosed_single_quote("cat \'Makefile          ");
	test_unclosed_single_quote("'Makefile          ");
	test_unclosed_single_quote("Makefile'");
	test_unclosed_single_quote("'''''");

	printf("\ntest: unclosed double quotes\n");
	test_unclosed_double_quote("cat \"Makefile");
	test_unclosed_double_quote("cat \"Makefile          ");
	test_unclosed_double_quote("\"Makefile          ");
	test_unclosed_double_quote("Makefile\"");
	test_unclosed_double_quote("\"\"\"\"\"");
	return (0);
	*/