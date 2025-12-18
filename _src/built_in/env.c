/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:06 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/17 23:59:38 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <map.h>
#include <stdio.h>
#include <minilibft.h>

int	builtin_env(t_ast_node *node, t_map_str_str *env)
{
	t_map_str_str	*current;

	(void)node;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->value, "") != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
