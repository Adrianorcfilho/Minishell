/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:58:22 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/07 23:49:44 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTE: This structure is assumed based on common shell implementations.
// You may need to adjust based on your actual t_ast_node definition.
/*
typedef struct s_ast_node
{
	// ... other members
	t_list_str *args; // A linked list of strings (the arguments)
	// ... other members
}	t_ast_node;
*/

// A basic structure for a linked list of strings (arguments)

#include <AST.h>
#include <map.h>
#include <stdio.h>
#include <string.h>

int	builtin_echo(t_ast_node *node, t_map_str_str *env)
{
	int	i;
	int	has_n_flag;

	(void)env;
	if (!node || node->arg_count == 0)
		return (printf("\n"), 0);
	has_n_flag = 0;
	if (node->arg_count > 0 && strcmp(node->args[0], "-n") == 0)
	{
		has_n_flag = 1;
		i = 1;
	}
	else
		i = 0;
	while (i < node->arg_count)
	{
		printf("%s", node->args[i]);
		if (i < node->arg_count - 1)
			printf(" ");
		i++;
	}
	if (has_n_flag == 0)
		printf("\n");
	return (0);
}
