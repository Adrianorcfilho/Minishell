/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:55:40 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/03 00:16:16 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && i < size - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*c;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc((size + 1) * (sizeof(char)));
	if (!c)
		return (NULL);
	ft_strlcpy(c, (char *)s1, size + 1);
	ft_strlcat(c, (char *)s2, size + 1);
	return (c);
}
