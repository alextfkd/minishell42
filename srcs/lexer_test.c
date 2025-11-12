#include "minishell.h"
#include "lexer.h"

volatile sig_atomic_t	g_sig_received = 0;

void	test_cat(char *target)
{
	t_token	*token;
	t_token	*head;
	int		status;

	status = 0;
	token = tokenize(target);
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

int	main(void)
{
	t_token *token;
	token = tokenize("  ");
	log_debug_show_token(token, LOG_DEBUG);
	test_cat("cat");
	test_cat("   cat   ");
	test_cat("cat      ");
	test_cat("      cat");
	test_cat("\tcat\t");
	test_cat("\ncat\n");
	test_binls("/bin/ls");
	test_binls(" /bin/ls ");
	test_binls("\n/bin/ls");
	test_binls("/bin/ls\n ");
	return (0);
}