/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:49:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/20 05:23:31 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

volatile sig_atomic_t	g_sig_received = 0;

void	test_empty(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target, &status);
	head = token;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_cat(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target, &status);
	head = token;
	if (strcmp(token->data, "cat") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_binls(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "/bin/ls") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_2cmd(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "cmd") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_2cmd1pipe(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "cmd1") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg1") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "|") && token->tk == TK_PIPE)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "cmd2") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg2") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_3cmd2pipe(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "cmd1") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg1") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "|") && token->tk == TK_PIPE)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "cmd2") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg2") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "|") && token->tk == TK_PIPE)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "cmd3") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (strcmp(token->data, "arg3") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_cat_parenthesis(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "(cat)") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_cat_single_quote(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, "\' cat \'") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_single_quoted_empty(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	//log_debug_show_token(token, LOG_DEBUG);
	head = token;
	if (strcmp(token->data, "\'\'") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_double_quoted_empty(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
	//log_debug_show_token(token, LOG_DEBUG);
	head = token;
	if (strcmp(token->data, "\"\"") && token->tk == TK_CHAR)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_unclosed_single_quote(char *target)
{
	t_token	*token;
	int		status;

	status = 0;
	token = tokenize(target);
	if (token->state != S_SQUOTE)
		status = 1;
	free_tokens(token);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_unclosed_double_quote(char *target)
{
	t_token	*token;
	int		status;

	status = 0;
	token = tokenize(target);
	if (token->state != S_DQUOTE)
		status = 1;
	free_tokens(token);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

void	test_single_red_in(char *target)
{
	t_token	*token;
	int		status;
	t_token	*head;

	status = 0;
	token = tokenize(target);
	head = token;
	if (strcmp(token->data, ">") != 0 && token->tk == TK_RED_IN)
		status = 1;
	token = token->next;
	if (token != NULL)
		status = 1;
	free_tokens(head);
	if (status)
		printf("[%s] -> ERROR\n", target);
	else
		printf("[%s] -> PASS\n", target);
}

int	main(void)
{
	//t_token *token;
	//token = tokenize("  ");
	//log_debug_show_token(token, LOG_DEBUG);
	printf("test: empty input\n");
	test_empty("");
	test_empty("           ");
	test_empty("    \n       ");

	printf("\ntest: cat only\n");
	test_cat("cat");
	test_cat("   cat   ");
	test_cat("cat      ");
	test_cat("      cat");
	test_cat("\tcat\t");
	test_cat("\ncat\n");

	printf("\ntest: cmd1\n");
	test_binls("/bin/ls");
	test_binls(" /bin/ls ");
	test_binls("\n/bin/ls");
	test_binls("/bin/ls\n ");

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
}