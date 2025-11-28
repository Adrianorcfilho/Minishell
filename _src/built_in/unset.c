/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:15 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/27 15:19:36 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <map.h>
#include <minilibft.h>

int	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_ast_node *node, t_map_str_str **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (i < node->arg_count)
	{
		if (!is_valid_identifier(node->args[i]))
			status = 1;
		else
		{
			map_unset(env, node->args[i]);
		}
		i++;
	}
	return (status);
}
