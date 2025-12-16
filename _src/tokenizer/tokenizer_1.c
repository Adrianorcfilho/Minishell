/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:36:15 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 22:02:33 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <tokenizer.h>
#include <unistd.h>

void	handle_word_check_quotes(char *input, char *in_quote, int *i)
{
	while (input[*i])
	{
		if (input[*i] == '\'' && (*in_quote == 0 || *in_quote == '\''))
		{
			if (*in_quote == '\'')
				*in_quote = 0;
			else
				*in_quote = '\'';
			(*i)++;
			continue ;
		}
		else if (input[*i] == '"' && (*in_quote == 0 || *in_quote == '"'))
		{
			if (*in_quote == '"')
				*in_quote = 0;
			else
				*in_quote = '"';
			(*i)++;
			continue ;
		}
		if (*in_quote == 0 && ft_strchr(" |><", input[*i]))
			break ;
		(*i)++;
	}
}

int	handle_word(char *input, t_token **tokens)
{
	char	*word;
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	handle_word_check_quotes(input, &in_quote, &i);
	word = ft_strndup(input, i);
	if (!word)
		return (i);
	link_tokens(tokens, create_token(TOKEN_TYPE_WORD, word));
	free(word);
	return (i);
}

t_token	*tokenize(char *prompt)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && ft_strchr(" ", prompt[i]))
			i++;
		if (ft_strchr("|><", prompt[i]))
			i += handle_special(prompt, i, &tokens);
		else if (prompt[i])
			i += handle_word(&prompt[i], &tokens);
	}
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

/*
int	main(int argc, char **argv)
{
	t_token	*tokens;

	tokens = tokenize(argv[1]);
	display_tokens(tokens);
	return (0);
}
*/
