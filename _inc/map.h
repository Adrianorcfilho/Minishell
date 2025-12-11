/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:49 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/11 23:06:43 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_global_vars
{
	char					*const_pwd;
}							t_global_vars;

typedef struct s_map_str_str
{
	char					*key;
	char					*value;
	struct s_map_str_str	*next;
}							t_map_str_str;

t_map_str_str				*env_init(char **env, t_global_vars *vars);
char						*map_get(t_map_str_str *head, const char *key);
int							map_unset(t_map_str_str **env, const char *key);
int							map_set(t_map_str_str **env, const char *key,
								const char *value);
void						map_print(t_map_str_str *env);
void						free_map(t_map_str_str *env);
char						**map_as_c_array(t_map_str_str *env);
t_map_str_str				*map_insert(const char *key, const char *value);

#endif
