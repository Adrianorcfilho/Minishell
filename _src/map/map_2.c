/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:35:33 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/07 23:36:05 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	map_unset(t_map_str_str **env, const char *key)
{
	t_map_str_str	*curr;
	t_map_str_str	*prev;

	prev = NULL;
	if (!env || !*env || !key)
		return (-1);
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (-1);
}
