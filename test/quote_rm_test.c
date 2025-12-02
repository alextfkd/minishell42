/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_rm_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:59:27 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/12/02 20:17:18 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "types.h"

volatile sig_atomic_t	g_sig_received = 0;

t_token	*remove_quote_from_token(t_token *token)
{
	t_ltstate	state;
	int			len;
	char		*new_data;

	if (!token || !token->data)
		return (NULL);
	len = ft_strlen(token->data);
	if (token->data[0] == '\'' && token->data[len - 1] == '\'')
		state = LT_SQUOTE;
	else if (token->data[0] == '\"' && token->data[len - 1] == '\"')
		state = LT_DQUOTE;
	else
		state = LT_NORMAL;
	new_data = remove_quote(token->data, state);
	free(token->data);
	token->data = new_data;
	return (token);
}

int	main(int argc, char **argv)
{
	char	*out;
	(void)argc;
	out = remove_quote(argv[1], ft_atoi(argv[2]));
	ft_putendl_fd(out, 1);
	free(out);
}
