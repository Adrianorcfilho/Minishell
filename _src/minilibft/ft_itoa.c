/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:25 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/26 22:50:41 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	fill_number(char *dst, long int n, int count)
{
	int	start;

	start = 0;
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		start = 1;
	}
	while (count > start)
	{
		count--;
		dst[count] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int num)
{
	char		*dst;
	int			count;
	long int	n;

	n = num;
	count = count_size(n);
	if (n < 0)
		count++;
	dst = (char *)malloc((count + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	dst[count] = '\0';
	fill_number(dst, n, count);
	return (dst);
}
