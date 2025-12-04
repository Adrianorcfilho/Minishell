/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:57 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 22:48:21 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include <error_log.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer.h>

// Parse commands,
// Need to handle things
//

static char	*strip_quotes(const char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len
				- 1] == '\''))
		{
			result = ft_substr(str, 1, len - 2);
			return (result);
		}
	}
	return (ft_strdup(str));
}

static t_ast_node	*handle_redirection(t_ast_node *cmd_node, t_token **current)
{
	t_ast_node	*redirect_node;
	t_token		*token;

	token = *current;
	redirect_node = create_ast_node(token_type_to_node_type(token->type));
	if (!redirect_node)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	token = token->next;
	if (!token || token->type != TOKEN_TYPE_WORD)
	{
		ft_putendl_fd(UNEXPECTED_TK_NEW_LINE, 2);
		free(redirect_node);
		free_ast(cmd_node);
		*current = token;
		return (NULL);
	}
	if (redirect_node->type == NODE_HEREDOC)
		redirect_node->heredoc_delimiter = ft_strdup(token->value);
	else
		redirect_node->filename = ft_strdup(token->value);
	redirect_node->left = cmd_node;
	*current = token->next;
	return (redirect_node);
}

t_ast_node	*parse_simple_command(t_token **current)
{
	t_ast_node	*cmd_node;
	t_ast_node	*root;
	t_token		*token;
	t_ast_node	*redirect_node;

	cmd_node = create_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (NULL);
	root = cmd_node; // Keep track of the tree root (changes with redirections)
	token = *current;
	while (token && token->type != TOKEN_TYPE_PIPE)
	{
		if (token->type == TOKEN_TYPE_WORD)
		{
			// ALWAYS add arguments to cmd_node (the original command node)
			add_arg_to_node(cmd_node, token->value);
			token = token->next;
		}
		else if (token->type >= TOKEN_TYPE_REDIRECT_IN
			&& token->type <= TOKEN_TYPE_HEREDOC)
		{
			// Create redirection node
			redirect_node = create_ast_node(token_type_to_node_type(token->type));
			if (!redirect_node)
			{
				free_ast(root);
				return (NULL);
			}
			token = token->next; // Move to filename
			if (!token || token->type != TOKEN_TYPE_WORD)
			{
				ft_putendl_fd(UNEXPECTED_TK_NEW_LINE, 2);
				free(redirect_node);
				free_ast(root);
				*current = token;
				return (NULL);
			}
			// Store filename (remove quotes if needed)
			if (redirect_node->type == NODE_HEREDOC)
				redirect_node->heredoc_delimiter = ft_strdup(token->value);
			else
				redirect_node->filename = ft_strdup(token->value);
			// Link: redirection wraps current root
			redirect_node->left = root;
			root = redirect_node; // Update root
			token = token->next;  // Move past filename
									// IMPORTANT: Continue the loop to collect more args!
		}
		else
			break ;
	}
	*current = token;
	return (root); // Return root (might be redirection or command)
}

t_ast_node	*parse_pipeline(t_token *tokens)
{
	t_ast_node	*left;
	t_token		*current;
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOKEN_TYPE_PIPE)
	{
		ft_putendl_fd(UNEXPECTED_TK_PIPE, 2);
		return (NULL);
	}
	current = tokens;
	left = parse_simple_command(&current);
	if (!left)
		return (NULL);
	while (current && current->type == TOKEN_TYPE_PIPE)
	{
		current = current->next;
		if (!current || current->type == TOKEN_TYPE_PIPE)
		{
			ft_putendl_fd(UNEXPECTED_TK_PIPE, 2);
			free_ast(left);
			return (NULL);
		}
		right = parse_simple_command(&current);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_node = create_ast_node(NODE_PIPE);
		if (!pipe_node)
		{
			free_ast(left);
			free_ast(right);
			return (NULL);
		}
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (i < node->arg_count)
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->filename)
		free(node->filename);
	if (node->heredoc_delimiter)
		free(node->heredoc_delimiter);
	if (node->heredoc_content)
		free(node->heredoc_content);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
