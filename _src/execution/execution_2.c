/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:55:32 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 23:05:28 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <stdlib.h>

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
		if (args[i][0] != '\0')
		{
			if (i != j)
				args[j] = args[i];
			j++;
		}
		else
		{
			free(args[i]);
		}
		i++;
	}
	args[j] = NULL;
	return (j);
}
