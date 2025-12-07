/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:58:22 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/28 12:02:40 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
