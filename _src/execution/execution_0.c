/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:20 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/11 23:06:59 by adrocha-         ###   ########.fr       */
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
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	run_builtin(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *exit_stauts)
{
	if (!node || !node->args || !node->args[0])
		return (-1);
	if (strcmp(node->args[0], "exit") == 0)
		return (builtin_exit(node, env, exit_stauts));
	else if (strcmp(node->args[0], "pwd") == 0)
		return (builtin_pwd(env, vars));
	else if (strcmp(node->args[0], "cd") == 0)
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

void	check_not_exec(t_ast_node *node)
{
	struct stat	st;

	if (ft_strchr(node->args[0], '/') != NULL)
	{
		if (stat(node->args[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			fprintf(stderr, "%s: is a directory\n", node->args[0]);
			exit(126);
		}
		if (access(node->args[0], F_OK) != 0)
		{
			perror(node->args[0]);
			exit(127);
		}
		if (access(node->args[0], X_OK) != 0)
		{
			perror(node->args[0]);
			exit(126);
		}
	}
}

void	check_is_error(t_ast_node *node)
{
	if (errno == ENOENT)
	{
		fprintf(stderr, "%s: command not found\n", node->args[0]);
		exit(127);
	}
	else if (errno == EACCES)
	{
		perror(node->args[0]);
		exit(126);
	}
	else
	{
		perror(node->args[0]);
		exit(126);
	}
}

void	find_path_and_exec(t_ast_node *node, t_map_str_str **env)
{
	char	*cmd_path;
	char	**env_array;

	check_not_exec(node);
	cmd_path = find_cmd_path(*env, node->args[0]);
	if (cmd_path == NULL)
	{
		if (ft_strchr(node->args[0], '/') == NULL)
		{
			ft_putstr_fd(node->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		cmd_path = node->args[0];
	}
	env_array = map_as_c_array(*env);
	execve(cmd_path, node->args, env_array);
	ft_free(env_array);
	check_is_error(node);
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
		find_path_and_exec(node, env);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
