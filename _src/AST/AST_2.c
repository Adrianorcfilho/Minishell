/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:58:39 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/15 16:04:21 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include <error_log.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer.h>

#define TK_TYPE_TO_ND_TYPE token_type_to_node_type

static t_ast_node	*handle_word_token(t_ast_node *cmd_node, t_token **token)
{
	add_arg_to_node(cmd_node, (*token)->value);
	*token = (*token)->next;
	return (cmd_node);
}

static t_ast_node	*handle_redirect(t_ast_node *root, t_token **token)
{
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node(TK_TYPE_TO_ND_TYPE((*token)->type));
	if (!redirect_node)
		return (free_ast(root), NULL);
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN_TYPE_WORD)
	{
		ft_putendl_fd(UNEXPECTED_TK_NEW_LINE, 2);
		return (free(redirect_node), free_ast(root), NULL);
	}
	if (redirect_node->type == NODE_HEREDOC)
		redirect_node->heredoc_delimiter = ft_strdup((*token)->value);
	else
		redirect_node->filename = ft_strdup((*token)->value);
	redirect_node->left = root;
	*token = (*token)->next;
	return (redirect_node);
}

t_ast_node	*parse_simple_command(t_token **current)
{
	t_ast_node	*cmd_node;
	t_ast_node	*root;
	t_token		*token;

	cmd_node = create_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (NULL);
	root = cmd_node;
	token = *current;
	while (token && token->type != TOKEN_TYPE_PIPE)
	{
		if (token->type == TOKEN_TYPE_WORD)
			handle_word_token(cmd_node, &token);
		else if (token->type >= TOKEN_TYPE_REDIRECT_IN
			&& token->type <= TOKEN_TYPE_HEREDOC)
		{
			root = handle_redirect(root, &token);
			if (!root)
				return (*current = token, NULL);
		}
		else
			break ;
	}
	return (*current = token, root);
}
