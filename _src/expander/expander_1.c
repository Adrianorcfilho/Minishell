/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:12 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/27 17:45:55 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <stdlib.h>

char    *exp_get_var_value(const char *src, int *i, t_map_str_str *env, 
    int exit_status)
{
    int     var_len;
    char    *var_name;
    char    *value;

    (*i)++; // Skip the '$'
    
    // Check if there's anything after $
    if (!src[*i])
        return (NULL); // Just a $ at end
    
    var_len = get_var_name_size(&src[*i]);
    if (var_len == 0)
        return (NULL); // No valid variable name (like "$ " or "$@")
    
    var_name = ft_substr(src, *i, var_len);
    if (!var_name)
        return (NULL);
    
    *i += var_len; // Move past the variable name
    value = get_var_value(var_name, env, exit_status);
    free(var_name);
    return (value);
}

int	exp_update_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
	{
		*sq = !(*sq);
		return (1);
	}
	if (c == '"' && !(*sq))
	{
		*dq = !(*dq);
		return (1);
	}
	return (0);
}

static int	handle_var(const char *str, int *i, t_map_str_str *env,
		int exit_status)
{
	char	*value;
	int		len;

	value = exp_get_var_value(str, i, env, exit_status);
	if (!value)
		return (1);
	len = ft_strlen(value);
	free(value);
	return (len);
}

int	calc_expanded_size(const char *str, t_map_str_str *env, int exit_status)
{
	int	i;
	int	len;
	int	sq;
	int	dq;

	i = 0;
	len = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (exp_update_quotes(str[i], &sq, &dq) || str[i] != '$' || !str[i + 1]
			|| sq)
		{
			len++;
			i++;
		}
		else
			len += handle_var(str, &i, env, exit_status);
	}
	return (len);
}
