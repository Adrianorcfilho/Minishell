/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:36:06 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/17 23:41:47 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <stdlib.h>
#include <tokenizer.h>
#include <execution.h>

static void	insert_split_tokens_after(t_token *current, t_token *split_tokens)
{
	t_token	*last_split;

	free(current->value);
	current->value = ft_strdup(split_tokens->value);
	if (split_tokens->next)
	{
		last_split = split_tokens;
		while (last_split->next)
			last_split = last_split->next;
		last_split->next = current->next;
		current->next = split_tokens->next;
		split_tokens->next = NULL;
	}
	free_tokens(split_tokens);
}

static void	handle_word_splitting(t_token *current, char *unquoted)
{
	t_token	*split_tokens;

	split_tokens = split_into_tokens(unquoted);
	if (split_tokens)
		insert_split_tokens_after(current, split_tokens);
	else
	{
		free(current->value);
		current->value = unquoted;
	}
}

static void	handle_no_splitting(t_token *current, char *unquoted)
{
	free(current->value);
	current->value = unquoted;
}

static void	process_word_token(t_token *current, t_map_str_str *map_env,
		int last_status)
{
	char	*original;
	char	*expanded;
	char	*unquoted;

	original = ft_strdup(current->value);
	expanded = expand_variables(current->value, map_env, last_status);
	unquoted = remove_outer_quotes(expanded);
	if (needs_word_splitting(original, unquoted))
		handle_word_splitting(current, unquoted);
	else
		handle_no_splitting(current, unquoted);
	free(original);
	free(expanded);
}

void	expand_tokens(t_token *tokens, t_map_str_str *map_env, int last_status)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_TYPE_WORD)
			process_word_token(current, map_env, last_status);
		current = next;
	}
}
