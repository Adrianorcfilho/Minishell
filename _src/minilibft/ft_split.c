/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:21:33 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/03 00:26:14 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minilibft.h>

int	count_words(const char *s, char c)
{
	int	count;
	int	nw;

	count = 0;
	nw = 0;
	while (*s)
	{
		if (*s != c && nw == 0)
		{
			count++;
			nw = 1;
		}
		else if (*s == c)
		{
			nw = 0;
		}
		s++;
	}
	return (count);
}

char	*new_string(const char *s, char c)
{
	char	*new;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s, len + 1);
	return (new);
}

 void	ft_free(char **res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		if (!(*res))
			return ;
		free(res[i]);
		i++;
	}
	free(res);
}

char	**ft_newsplit(char **res, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			res[i] = new_string(s, c);
			if (!res[i])
			{
				ft_free(res);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	res[i] = (NULL);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_newsplit(res, s, c));
}
