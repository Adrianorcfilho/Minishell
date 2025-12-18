/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:22:11 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/17 23:38:37 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <stdlib.h>
#include <tokenizer.h>

static int	should_skip_quote(char c, char *in_quote)
{
	if (!*in_quote && (c == '"' || c == '\''))
	{
		*in_quote = c;
		return (1);
	}
	if (*in_quote && c == *in_quote)
	{
		*in_quote = 0;
		return (1);
	}
	return (0);
}

char	*remove_outer_quotes(char *str)
{
	char	*result;
	char	in_quote;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if (should_skip_quote(str[i], &in_quote))
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	needs_word_splitting(const char *original, const char *expanded)
{
	if (original[0] == '"' || original[0] == '\'')
		return (0);
	if (ft_strchr(original, '$') && ft_strchr(expanded, ' '))
		return (1);
	return (0);
}

void	link_word_tokens(t_token *head, char **words)
{
	t_token	*current;
	int		i;

	current = head;
	i = 1;
	while (words[i])
	{
		current->next = create_token(TOKEN_TYPE_WORD, words[i]);
		if (!current->next)
		{
			free_tokens(head);
			return ;
		}
		current = current->next;
		i++;
	}
}

t_token	*split_into_tokens(const char *str)
{
	char	**words;
	t_token	*head;

	words = ft_split(str, ' ');
	if (!words || !words[0])
	{
		if (words)
			ft_free(words);
		return (NULL);
	}
	head = create_token(TOKEN_TYPE_WORD, words[0]);
	if (!head)
	{
		ft_free(words);
		return (NULL);
	}
	link_word_tokens(head, words);
	ft_free(words);
	return (head);
}

/*
void	expand_tokens(t_token *tokens, t_map_str_str *map_env, int last_status)
{
	t_token	*current;
	t_token	*next;
	t_token	*split_tokens;
	t_token	*last_split;
	char	*expanded;
	char	*unquoted;
	char	*original;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_TYPE_WORD)
		{
			original = ft_strdup(current->value);
			expanded = expand_variables(current->value, map_env, last_status);
			unquoted = remove_outer_quotes(expanded);
			if (needs_word_splitting(original, unquoted))
			{
				split_tokens = split_into_tokens(unquoted);
				if (split_tokens)
				{
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
				else
				{
					free(current->value);
					current->value = unquoted;
					unquoted = NULL;
				}
			}
			else
			{
				free(current->value);
				current->value = unquoted;
				unquoted = NULL;
			}
			free(original);
			free(expanded);
			if (unquoted)
				free(unquoted);
		}
		current = next;
	}
}
*/
