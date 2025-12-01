/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:49:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/27 16:14:08 by tkatsuma         ###   ########.fr       */
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
		printf("test -> %s, expected -> %s\n", input, expected);
		return (0);
	}
	return (1);
}

int	test_single_cmd(t_shell *shell, char *input, char *cmd1, char *path1)
{
	t_astree	*astree;
	t_astree	*astree_head;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	astree_head = astree;
	shell->status = parameter_expansion(shell->app, astree);
	if (ft_assert_str(astree->cmd->argv[0], cmd1) &&
		ft_assert_str(astree->cmd->argv[1], path1)
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	
	astree_clear(&astree_head);
	return (status);
}

int	test_cmd1_arg1_red1(t_shell *shell, char *input, char *cmd1, char *arg1, char *red1)
{
	t_astree	*astree;
	t_astree	*astree_head;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	astree_head = astree;
	shell->status = parameter_expansion(shell->app, astree);
	if (ft_assert_str(astree->cmd->argv[0], cmd1) &&
		ft_assert_str(astree->cmd->argv[1], arg1) &&
		ft_assert_str(astree->cmd->red->file, red1)
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	
	astree_clear(&astree_head);
	return (status);
}

int	test_cmd1_arg1_red2(t_shell *shell, char *input, char *cmd1, char *arg1, char *red1, char *red2)
{
	t_astree	*astree;
	t_astree	*astree_head;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	astree_head = astree;
	shell->status = parameter_expansion(shell->app, astree);
	if (ft_assert_str(astree->cmd->argv[0], cmd1) &&
		ft_assert_str(astree->cmd->argv[1], arg1) &&
		ft_assert_str(astree->cmd->red->file, red1) &&
		ft_assert_str(astree->cmd->red->next->file, red2)
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	
	astree_clear(&astree_head);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int	status;

	shell = create_t_shell(argc, argv, envp);

	status = 0;
	//status += test_single_cmd(NULL);
	status += test_single_cmd(shell, "cat $LANG", "cat", "en_US.UTF-8");
	status += test_single_cmd(shell, "cat \'$LANG\'", "cat", "$LANG");
	status += test_single_cmd(shell, "cat \"$LANG\"", "cat", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat $LANG > out", "cat", "en_US.UTF-8", "out");
	status += test_cmd1_arg1_red1(shell, "cat $LANG > $LANG", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat $LANG < $LANG", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat $LANG << $LANG", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat $LANG >> $LANG", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat \'$LANG\' > \'$LANG\'", "cat", "$LANG", "$LANG");
	status += test_cmd1_arg1_red1(shell, "cat \'$LANG\' < \'$LANG\'", "cat", "$LANG", "$LANG");
	status += test_cmd1_arg1_red1(shell, "cat \'$LANG\' << \'$LANG\'", "cat", "$LANG", "$LANG");
	status += test_cmd1_arg1_red1(shell, "cat \'$LANG\' >> \'$LANG\'", "cat", "$LANG", "$LANG");
	status += test_cmd1_arg1_red1(shell, "cat \"$LANG\" > \"$LANG\"", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat \"$LANG\" < \"$LANG\"", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat \"$LANG\" << \"$LANG\"", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red1(shell, "cat \"$LANG\" >> \"$LANG\"", "cat", "en_US.UTF-8", "en_US.UTF-8");
	status += test_cmd1_arg1_red2(shell, "cat $LANG >> $LANG > $LANG", "cat", "en_US.UTF-8", "en_US.UTF-8", "en_US.UTF-8");
	free_shell(shell);
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