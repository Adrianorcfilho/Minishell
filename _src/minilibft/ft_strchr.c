/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:30 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/25 09:35:31 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			temp;

	temp = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == temp)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == temp)
		return ((char *)&s[i]);
	return (NULL);
}
