/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:49:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/27 16:13:12 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

volatile sig_atomic_t	g_sig_received = 0;

/*
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
*/

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
	astree_clear(&astree);
	return (status);
}

int	test_cmd1_arg1(char *input, char *cmd1, char *arg1)
{
	t_astree	*astree;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	if (
		ft_assert_str(astree->cmd->argv[0], cmd1) && 
		ft_assert_str(astree->cmd->argv[1], arg1) 
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	astree_clear(&astree);
	return (status);
}

int	test_cmd1_arg2(char *input, char *cmd1, char *arg1, char *arg2)
{
	t_astree	*astree;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	if (
		ft_assert_str(astree->cmd->argv[0], cmd1) && 
		ft_assert_str(astree->cmd->argv[1], arg1) &&
		ft_assert_str(astree->cmd->argv[2], arg2) 
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	astree_clear(&astree);
	return (status);
}

int	test_cmd1_arg1_pipe_cmd2_arg2(
	char *input, char *cmd1, char *arg1, char *cmd2, char *arg2)
{
	t_astree	*astree;
	t_astree	*head;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	head = astree;
	if (astree->type != NODE_PIPE || status > 0)
		status++;
	if (
		astree->left->type != NODE_CMD || 
		!ft_assert_str(astree->left->cmd->argv[0], cmd1) || 
		!ft_assert_str(astree->left->cmd->argv[1], arg1)
	)
		status++;
	if (
		astree->right->type != NODE_CMD || 
		!ft_assert_str(astree->right->cmd->argv[0], cmd2) || 
		!ft_assert_str(astree->right->cmd->argv[1], arg2)
	)
		status++;
	if (status > 0)
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	else
		printf("[%s] -> PASS (status: %d)\n", input, status);
	astree_clear(&head);
	return (status);
}

int	test_cmd1_arg1_pipe_cmd2_arg2_pipe_cmd3_arg3(
	char *input, char *cmd1, char *arg1, char *cmd2, char *arg2, char *cmd3, char *arg3)
{
	t_astree	*astree;
	t_astree	*head;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	head = astree;
	if (astree->type != NODE_PIPE || status > 0)
		status++;
	if (
		astree->right->type != NODE_CMD || 
		!ft_assert_str(astree->right->cmd->argv[0], cmd1) || 
		!ft_assert_str(astree->right->cmd->argv[1], arg1)
	)
		status++;
	astree = astree->left;
	if (astree->type != NODE_PIPE || status > 0)
		status++;
	if (
		astree->right->type != NODE_CMD || 
		!ft_assert_str(astree->right->cmd->argv[0], cmd2) || 
		!ft_assert_str(astree->right->cmd->argv[1], arg2)
	)
		status++;
	if (
		astree->left->type != NODE_CMD || 
		!ft_assert_str(astree->left->cmd->argv[0], cmd3) || 
		!ft_assert_str(astree->left->cmd->argv[1], arg3)
	)
		status++;
	if (status > 0)
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	else
		printf("[%s] -> PASS (status: %d)\n", input, status);
	astree_clear(&head);
	return (status);
}

int	test_cmd1_arg1_red1(char *input, char *cmd1, char *arg1, char *red1, t_tkind kind)
{
	t_astree	*astree;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	if (
		ft_assert_str(astree->cmd->argv[0], cmd1) && 
		ft_assert_str(astree->cmd->argv[1], arg1) &&
		astree->cmd->red->tk == kind &&
		ft_assert_str(astree->cmd->red->file, red1)
	)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	astree_clear(&astree);
	return (status);
}

int	test_failure(char *input)
{
	t_astree	*astree;
	t_token		*token;
	int			status;

	status = 0;
	token = tokenize(input, &status);
	astree = create_astree_from_tokens(&token, &status);
	if (astree == NULL && status == 1)
		printf("[%s] -> PASS (status: %d)\n", input, status);
	else
		printf("[%s] -> FAIL (status: %d)\n", input, status);
	astree_clear(&astree);
	return (status);
}

int	main(void)
{
	int	status;

	status = 0;
	//status += test_single_cmd(NULL);
	status += test_single_cmd("ls");
	status += test_single_cmd("/bin/ls");
	status += test_cmd1_arg1("/bin/ls arg1", "/bin/ls", "arg1");
	status += test_cmd1_arg1_pipe_cmd2_arg2("ls ./ | cat -e", "ls", "./", "cat", "-e");
	status += test_cmd1_arg1_pipe_cmd2_arg2_pipe_cmd3_arg3(
		"ls ./ | cat -e | grep .c", "grep", ".c", "cat", "-e", "ls", "./");
	status += test_cmd1_arg1_red1(
		"ls ./ > out", "ls", "./", "out", TK_RED_OUT
	);
	status += test_cmd1_arg1_red1(
		"> out ls ./", "ls", "./", "out", TK_RED_OUT
	);
	status += test_cmd1_arg1_red1(
		"ls < in ./", "ls", "./", "in", TK_RED_IN
	);
	status += test_cmd1_arg1_red1(
		"ls ./ >> append", "ls", "./", "append", TK_RED_APPEND
	);
	status += test_cmd1_arg1_red1(
		"ls ./ << heredoc", "ls", "./", "heredoc", TK_RED_HEREDOC
	);
	status += test_cmd1_arg1_red1(
		"ls ./ > $OUT", "ls", "./", "$OUT", TK_RED_OUT
	);
	status += test_cmd1_arg1_red1(
		"ls ./ > \'$OUT\'", "ls", "./", "\'$OUT\'", TK_RED_OUT
	);
	status += test_cmd1_arg1_red1(
		"ls ./ > \"$OUT\"", "ls", "./", "\"$OUT\"", TK_RED_OUT
	);
	status += test_failure( "ls ./ > > \"$OUT\"");
	status += test_failure( "ls ./ > out > > out2");
	status += test_failure( "> out > out2 << < ls");
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