/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:22:11 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/15 16:31:34 by ide-abre         ###   ########.fr       */
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

void	expand_tokens(t_token *tokens, t_map_str_str *map_env, int last_status)
{
	t_token	*current;
	char	*expanded;
	char	*unquoted;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_TYPE_WORD)
		{
			expanded = expand_variables(current->value, map_env, last_status);
			unquoted = remove_outer_quotes(expanded);
			free(current->value);
			free(expanded);
			current->value = unquoted;
		}
		current = current->next;
	}
}
