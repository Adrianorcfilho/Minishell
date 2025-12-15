/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:35:12 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/15 16:20:40 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <stdlib.h>

static int	write_var(t_expand_ctx *ctx, int j, int *i)
{
	char	*val;
	int		len;

	val = exp_get_var_value(ctx->src, i, ctx->env, ctx->last_exit);
	if (!val)
	{
		ctx->dst[j++] = '$';
		return (j);
	}
	len = ft_strlen(val);
	ft_memcpy(&ctx->dst[j], val, len);
	free(val);
	return (j + len);
}

void	cpy_expansion(char *dst, const char *src, t_map_str_str *env,
		int exit_status)
{
	t_expand_ctx	ctx;
	int				i;
	int				j;
	int				sq;
	int				dq;

	ctx.dst = dst;
	ctx.src = src;
	ctx.env = env;
	ctx.last_exit = exit_status;
	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	while (src[i])
	{
		if (exp_update_quotes(src[i], &sq, &dq))
			dst[j++] = src[i++];
		else if (src[i] == '$' && !sq)
			j = write_var(&ctx, j, &i);
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
}

char	*expand_variables(const char *str, t_map_str_str *env, int last_exit)
{
	int		len;
	char	*out;

	if (!str)
		return (NULL);
	len = calc_expanded_size(str, env, last_exit);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	cpy_expansion(out, str, env, last_exit);
	return (out);
}
