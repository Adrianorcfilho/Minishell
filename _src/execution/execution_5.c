/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:23:07 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 03:12:14 by ide-abre         ###   ########.fr       */
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

static void	command_not_found(t_ast_node *node, t_global_vars *vars,
		t_map_str_str **env)
{
	ft_putstr_fd(node->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cleanup_and_exit(vars, env, 127);
}

static void	handle_local_file(t_ast_node *node, t_global_vars *vars,
		t_map_str_str **env)
{
	struct stat	st;

	if (access(node->args[0], F_OK) == 0)
	{
		if (stat(node->args[0], &st) == 0 && S_ISDIR(st.st_mode))
			command_not_found(node, vars, env);
		perror(node->args[0]);
		cleanup_and_exit(vars, env, 126);
	}
	command_not_found(node, vars, env);
}

void	find_path_and_exec(t_ast_node *node, t_global_vars *vars,
		t_map_str_str **env)
{
	char	*cmd_path;
	char	**env_array;
	int		should_free_path;

	check_not_exec(node, vars, env);
	cmd_path = find_cmd_path(*env, node->args[0]);
	should_free_path = (cmd_path != NULL);
	if (cmd_path == NULL)
	{
		if (ft_strchr(node->args[0], '/') == NULL)
			handle_local_file(node, vars, env);
		cmd_path = node->args[0];
	}
	env_array = map_as_c_array(*env);
	execve(cmd_path, node->args, env_array);
	ft_free(env_array);
	if (should_free_path)
		free(cmd_path);
	check_is_error(node, vars, env);
}
