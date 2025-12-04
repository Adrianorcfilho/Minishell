/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:10 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 22:47:55 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <map.h>
#include <minilibft.h>
#include <stdio.h>

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	export_set_pair(char *arg, char *equals, t_map_str_str **env)
{
	char	*key;
	char	*value;
	int		result;

	key = ft_strndup(arg, equals - arg);
	value = equals + 1;
	result = map_set(env, key, value);
	free(key);
	return (result == -1);
}

static int	export_handle_arg(char *arg, t_map_str_str **env)
{
	char	*equals;
	char	*key;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		key = ft_strndup(arg, equals - arg);
		if (!is_valid_identifier(key))
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
				arg);
			free(key);
			return (1); // invalid identifier
		}
		free(key);
		return (export_set_pair(arg, equals, env));
	}
	else
	{
		if (!is_valid_identifier(arg))
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
				arg);
			return (1);
		}
		if (!map_get(*env, arg))
			map_set(env, arg, "");
	}
	return (0);
}

int	builtin_export(t_ast_node *node, t_map_str_str **env)
{
	int	i;

	i = 1;
	if (node->arg_count == 1)
	{
		map_print(*env);
		return (0);
	}
	while (i < node->arg_count)
	{
		if (export_handle_arg(node->args[i], env) == 1)
			return (1);
		i++;
	}
	return (0);
}
