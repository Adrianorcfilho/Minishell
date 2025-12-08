/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:17 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/07 23:35:58 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	update_existing_key(t_map_str_str *current, const char *value)
{
	char	*new_value;

	if (value)
		new_value = ft_strdup(value);
	else
		new_value = ft_strdup("");
	if (!new_value)
		return (-1);
	free(current->value);
	current->value = new_value;
	return (0);
}

int	map_set(t_map_str_str **env, const char *key, const char *value)
{
	t_map_str_str	*current;
	t_map_str_str	*new;

	if (!env || !key)
		return (-1);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (update_existing_key(current, value));
		current = current->next;
	}
	new = map_insert(key, value);
	if (!new)
		return (-1);
	new->next = *env;
	*env = new;
	return (0);
}

static t_map_str_str	*parse_and_create_node(char *env_line)
{
	char			*equals;
	char			*key;
	char			*value;
	t_map_str_str	*new;

	equals = ft_strchr(env_line, '=');
	if (!equals)
		return (NULL);
	key = ft_strndup(env_line, equals - env_line);
	if (!key)
		return (NULL);
	value = equals + 1;
	new = map_insert(key, value);
	free(key);
	return (new);
}

int	set_two_null(t_map_str_str **a, t_map_str_str **b)
{
	*a = NULL;
	*b = NULL;
	return (1);
}

t_map_str_str	*env_init(char **env)
{
	t_map_str_str	*head;
	t_map_str_str	*curr;
	t_map_str_str	*new;
	int				i;

	if (set_two_null(&head, &curr) & (!env))
		return (NULL);
	i = 0;
	while (env[i])
	{
		new = parse_and_create_node(env[i++]);
		if (!new)
			continue ;
		if (!head)
		{
			head = new;
			curr = new;
		}
		else
		{
			curr->next = new;
			curr = new;
		}
	}
	return (head);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_map_str_str	*map_env;

	map_env = env_init(env);
	map_print(map_env);
	map_set(&map_env, "TESTE", "123");
	map_print(map_env);
	map_unset(&map_env, "LS_COLORS");
	map_print(map_env);
}
*/
