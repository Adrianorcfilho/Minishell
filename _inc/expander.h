/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:45 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/15 16:25:52 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <map.h>
# include <tokenizer.h>

typedef struct s_expand_ctx
{
	char			*dst;
	const char		*src;
	t_map_str_str	*env;
	int				last_exit;
}					t_expand_ctx;

char				*expand_variables(const char *str, t_map_str_str *env,
						int last_exit);
int					is_valid_var_char(char c);
int					get_var_name_size(const char *str);
char				*get_var_value(const char *var_name, t_map_str_str *env,
						int exit_status);
char				*exp_get_var_value(const char *src, int *i,
						t_map_str_str *env, int last_exit);

int					exp_update_quotes(char c, int *sq, int *dq);

int					calc_expanded_size(const char *str, t_map_str_str *env,
						int exit_status);
char				*remove_outer_quotes(char *str);
void				expand_tokens(t_token *tokens, t_map_str_str *map_env,
						int last_status);
#endif
