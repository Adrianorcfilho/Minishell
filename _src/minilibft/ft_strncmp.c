/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:40:56 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/11 23:10:01 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((int)(unsigned char)s1[i] - (unsigned char)s2[i]);
}
