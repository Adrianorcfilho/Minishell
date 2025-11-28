/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:55:32 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/28 09:56:58 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <stdlib.h>

// Filter out empty strings from args array after expansion
int	filter_empty_args(char **args)
{
	int	i;
	int	j;

	if (!args)
		return (0);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0') // Keep non-empty strings
		{
			if (i != j)
				args[j] = args[i];
			j++;
		}
		else
		{
			free(args[i]); // Free the empty string
		}
		i++;
	}
	args[j] = NULL;
	return (j); // Return new arg count
}
