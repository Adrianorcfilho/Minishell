/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:55 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/03 00:11:42 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <stdlib.h>

int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalnum(int c);
char	*ft_itoa(int num);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strcpy(char *s1, char *s2);
void	*ft_realloc(void *ptr, size_t size);
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_free(char **res);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
