/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:36:15 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 22:07:49 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <tokenizer.h>
#include <unistd.h>

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	link_tokens(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (*tokens == NULL)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static int	handle_redirect(char *input, int index, t_token **tokens, char c)
{
	if (input[index + 1] == c)
	{
		if (c == '<')
			link_tokens(tokens, create_token(TOKEN_TYPE_HEREDOC, "<<"));
		else
			link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_APPEND, ">>"));
		return (2);
	}
	if (c == '<')
		link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_IN, "<"));
	else
		link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_OUT, ">"));
	return (1);
}

int	handle_special(char *input, int index, t_token **tokens)
{
	if (input[index] == '|')
	{
		link_tokens(tokens, create_token(TOKEN_TYPE_PIPE, "|"));
		return (1);
	}
	else if (input[index] == '<')
		return (handle_redirect(input, index, tokens, '<'));
	else if (input[index] == '>')
		return (handle_redirect(input, index, tokens, '>'));
	return (0);
}
