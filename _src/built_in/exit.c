/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:29:59 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 02:45:25 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <limits.h>
#include <map.h>
#include <minilibft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	cleanup_and_exit(t_global_vars *vars, t_map_str_str **env,
		int exit_code)
{
	if (vars->current_tokens)
		free_tokens(vars->current_tokens);
	if (vars->current_ast)
		free_ast(vars->current_ast);
	if (vars->const_pwd)
		free(vars->const_pwd);
	free_map(*env);
	exit(exit_code);
}

static void	exit_with_cleanup(t_global_vars *vars, t_map_str_str **env,
		int code)
{
	if (vars->current_tokens)
		free_tokens(vars->current_tokens);
	if (vars->current_ast)
		free_ast(vars->current_ast);
	free_map(*env);
	free(vars->const_pwd);
	rl_clear_history();
	exit(code);
}

static int	is_numeric_argument(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *s)
{
	long long	res;
	long long	sign;

	res = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}

int	builtin_exit(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *exit_status)
{
	long long	code;

	printf("exit\n");
	if (node->arg_count == 1)
		exit_with_cleanup(vars, env, *exit_status);
	if (!is_numeric_argument(node->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_with_cleanup(vars, env, 2);
	}
	if (node->arg_count > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	code = (unsigned char)ft_atoll(node->args[1]);
	exit_with_cleanup(vars, env, code);
	return (0);
}
