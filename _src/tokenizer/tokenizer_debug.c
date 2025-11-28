/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:36:10 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/25 09:36:11 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>
#include <stdio.h>
#include <tokenizer.h>

void	display_tokens(t_token *tokens)
{
	char	*type_names[7];
	t_token	*token;

	type_names[0] = ft_strdup("WORD");
	type_names[1] = ft_strdup("PIPE");
	type_names[2] = ft_strdup("REDIRECT_IN");
	type_names[3] = ft_strdup("REDIRECT_OUT");
	type_names[4] = ft_strdup("REDIRECT_APPEND");
	type_names[5] = ft_strdup("HEREDOC");
	token = tokens;
	printf("Value\t\tType\n");
	printf("--------------\n");
	while (token)
	{
		printf("%s\t\t\t%s\n", token->value, type_names[(int)token->type]);
		token = token->next;
	}
}
