/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:21:40 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 23:02:01 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <minilibft.h>

int	validate_syntax(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_OUT)
	{
		if (!node->filename || !node->left)
		{
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (1);
		}
	}
	if (validate_syntax(node->left))
		return (1);
	if (validate_syntax(node->right))
		return (1);
	return (0);
}
