/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:20 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 03:21:06 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <AST.h>
#include <errno.h>
#include <error_log.h>
#include <execution.h>
#include <fcntl.h>
#include <map.h>
#include <minilibft.h>
#include <permitions.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	run_builtin(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *exit_stauts)
{
	if (!node || !node->args || !node->args[0])
		return (-1);
	if (ft_strcmp(node->args[0], "exit") == 0)
		return (builtin_exit(node, env, vars, exit_stauts));
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		return (builtin_pwd(env, vars));
	else if (ft_strcmp(node->args[0], "cd") == 0)
		return (builtin_cd(node, env, vars));
	else if (ft_strcmp(node->args[0], "export") == 0)
		return (builtin_export(node, env));
	else if (ft_strcmp(node->args[0], "unset") == 0)
		return (builtin_unset(node, env));
	else if (ft_strcmp(node->args[0], "env") == 0)
		return (builtin_env(node, *env));
	else if (ft_strcmp(node->args[0], "echo") == 0)
		return (builtin_echo(node, *env));
	return (1);
}

void	check_not_exec(t_ast_node *node, t_global_vars *vars,
		t_map_str_str **env)
{
	struct stat	st;

	if (ft_strchr(node->args[0], '/') != NULL)
	{
		if (stat(node->args[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(node->args[0], 2);
			ft_putendl_fd(": is a directory", 2);
			cleanup_and_exit(vars, env, 126);
		}
		if (access(node->args[0], F_OK) != 0)
		{
			perror(node->args[0]);
			cleanup_and_exit(vars, env, 127);
		}
		if (access(node->args[0], X_OK) != 0)
		{
			perror(node->args[0]);
			cleanup_and_exit(vars, env, 126);
		}
	}
}

void	check_is_error(t_ast_node *node, t_global_vars *vars,
		t_map_str_str **env)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_and_exit(vars, env, 127);
	}
	else if (errno == EACCES)
	{
		perror(node->args[0]);
		cleanup_and_exit(vars, env, 126);
	}
	else
	{
		perror(node->args[0]);
		cleanup_and_exit(vars, env, 126);
	}
}

int	exec_command(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *last_exit)
{
	pid_t	pid;
	int		status;

	if (!node || node->type != NODE_COMMAND)
		return (1);
	if (node->arg_count == 0 || !node->args[0] || !node->args[0][0])
		return (0);
	if (is_builtin(node->args[0]))
		return (run_builtin(node, env, vars, last_exit));
	pid = safe_fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		find_path_and_exec(node, vars, env);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
