/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:49 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/26 22:47:54 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include <stdio.h>

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

static void	display_command(t_ast_node *node)
{
	int	i;

	printf("COMMAND: ");
	i = 0;
	while (i < node->arg_count)
	{
		printf("%s ", node->args[i]);
		i++;
	}
	printf("\n");
}

static void	display_redirect(t_ast_node *node, int depth)
{
	const char	*type_name;

	if (node->type == NODE_REDIRECT_IN)
		type_name = "REDIRECT_IN";
	else if (node->type == NODE_REDIRECT_OUT)
		type_name = "REDIRECT_OUT";
	else if (node->type == NODE_REDIRECT_APPEND)
		type_name = "REDIRECT_APPEND";
	else
		type_name = "HEREDOC";
	printf("%s: %s\n", type_name, node->filename);
	display_ast(node->left, depth + 1);
}

static void	display_pipe(t_ast_node *node, int depth)
{
	printf("PIPE\n");
	display_ast(node->left, depth + 1);
	display_ast(node->right, depth + 1);
}

void	display_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_COMMAND)
		display_command(node);
	else if (node->type == NODE_PIPE)
		display_pipe(node, depth);
	else if (node->type >= NODE_REDIRECT_IN && node->type <= NODE_HEREDOC)
		display_redirect(node, depth);
}
