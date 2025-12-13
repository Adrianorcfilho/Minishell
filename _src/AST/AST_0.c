/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:57 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/13 21:38:14 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer.h>

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->arg_count = 0;
	node->filename = NULL;
	node->heredoc_content = NULL;
	node->heredoc_delimiter = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// static char	*remove_quotes(const char *arg)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	char	quote;

// 	result = malloc(ft_strlen(arg) + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	while (arg[i])
// 	{
// 		if ((arg[i] == '"' || arg[i] == '\'') && !quote)
// 			quote = arg[i++];
// 		else if (arg[i] == quote)
// 		{
// 			quote = 0;
// 			i++;
// 		}
// 		else
// 			result[j++] = arg[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

void	add_arg_to_node(t_ast_node *node, char *arg)
{
	char	**new_args;
	int		i;

	if (!arg || !arg[0])
		return ;
	new_args = malloc(sizeof(char *) * (node->arg_count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < node->arg_count)
	{
		new_args[i] = node->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	if (node->args)
		free(node->args);
	node->args = new_args;
	node->arg_count++;
}

t_node_type	token_type_to_node_type(t_token_type token_type)
{
	if (token_type == TOKEN_TYPE_REDIRECT_IN)
		return (NODE_REDIRECT_IN);
	if (token_type == TOKEN_TYPE_REDIRECT_OUT)
		return (NODE_REDIRECT_OUT);
	if (token_type == TOKEN_TYPE_REDIRECT_APPEND)
		return (NODE_REDIRECT_APPEND);
	if (token_type == TOKEN_TYPE_HEREDOC)
		return (NODE_HEREDOC);
	return (NODE_COMMAND);
}
