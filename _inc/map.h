/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:49 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/27 01:07:09 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map_str_str
{
	char					*key;
	char					*value;
	struct s_map_str_str	*next;
}							t_map_str_str;

t_map_str_str				*env_init(char **env);
char						*map_get(t_map_str_str *head, const char *key);
int							map_unset(t_map_str_str **env, const char *key);
int							map_set(t_map_str_str **env, const char *key,
								const char *value);
void						map_print(t_map_str_str *env);
void						free_map(t_map_str_str *env);
t_map_str_str				*map_insert(const char *key, const char *value);

#endif
