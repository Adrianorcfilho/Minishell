/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:17 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 22:42:01 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_map_str_str	*map_insert(const char *key, const char *value)
{
	t_map_str_str	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_map_str_str));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	free_map(t_map_str_str *env)
{
	t_map_str_str	*current;
	t_map_str_str	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

char	*map_get(t_map_str_str *head, const char *key)
{
	t_map_str_str	*current;

	current = head;
	if (!key)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	map_print(t_map_str_str *env)
{
	t_map_str_str	*current;

	current = env;
	while (current)
	{
		printf("key: %s value: %s\n", current->key, current->value);
		current = current->next;
	}
}

char	**map_as_c_array(t_map_str_str *env)
{
	char			**map_array;
	t_map_str_str	*current;
	int				count;
	int				arr_line_size;

	current = env;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	map_array = malloc(sizeof(char **) * count + 1);
	if (!map_array)
		return (NULL);
	current = env;
	count = 0;
	while (current)
	{
		arr_line_size = ft_strlen(current->key) + 1 + ft_strlen(current->value)
			+ 1;
		map_array[count] = malloc(sizeof(char *) * arr_line_size);
		map_array[count] = ft_strjoin(map_array[count], current->key);
		map_array[count] = ft_strjoin(map_array[count], "=");
		map_array[count] = ft_strjoin(map_array[count], current->value);
		current = current->next;
		count++;
	}
	map_array[count] = NULL;
	return (map_array);
}
