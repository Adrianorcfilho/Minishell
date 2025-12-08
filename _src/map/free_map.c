/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:14:25 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/07 23:16:51 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <stdlib.h>

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
