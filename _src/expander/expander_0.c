/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:12 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 22:42:35 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <minilibft.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int	get_var_name_size(const char *str)
{
	int	len;

	len = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '?')
		return (1);
	while (str[len] && is_valid_var_char(str[len]))
		len++;
	return (len);
}

char	*get_var_value(const char *var_name, t_map_str_str *env,
		int exit_status)
{
	char	*value;
	char	*exit_str;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_str = ft_itoa(exit_status);
		return (exit_str);
	}
	value = map_get(env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
