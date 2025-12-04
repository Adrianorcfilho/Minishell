/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:20 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 23:03:54 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <AST.h>
#include <errno.h>
#include <error_log.h>
#include <execution.h>
#include <fcntl.h>
#include <minilibft.h>
#include <permitions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	run_builtin(t_ast_node *node, t_map_str_str **env, int *exit_stauts)
{
	if (!node || !node->args || !node->args[0])
		return (-1);
	if (strcmp(node->args[0], "exit") == 0)
		return (builtin_exit(node, env, exit_stauts));
	else if (strcmp(node->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (strcmp(node->args[0], "cd") == 0)
		return (builtin_cd(node, env));
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

int	exec_command(t_ast_node *node, t_map_str_str **env, int *last_exit)
{
	pid_t		pid;
	int			status;
	struct stat	st;
	char		*cmd_path;
	char		**env_array;

	if (!node || node->type != NODE_COMMAND)
		return (1);
	if (node->arg_count == 0 || !node->args[0] || !node->args[0][0])
		return (0);
	if (is_builtin(node->args[0]))
		return (run_builtin(node, env, last_exit));
	pid = safe_fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (strchr(node->args[0], '/') != NULL)
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
		cmd_path = find_cmd_path(*env, node->args[0]);
		if (cmd_path == NULL)
			cmd_path = node->args[0];
		env_array = map_as_c_array(*env);
		execve(cmd_path, node->args, env_array);
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
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

char	*strip_quotes(const char *s)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	j = 0;
	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

int	safe_open(enum e_node_type type, char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	fd = -1;
	if (type == NODE_REDIRECT_IN)
		fd = open(filename, O_RDONLY);
	else if (type == NODE_REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, USER_RW_OTHERS_R);
	else if (type == NODE_REDIRECT_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, USER_RW_OTHERS_R);
	if (fd == -1)
		perror(filename);
	return (fd);
}

int	exec_node(t_ast_node *node, t_map_str_str **env, int *status)
{
	if (!node)
		return (-1);
	if (node->type == NODE_COMMAND)
		return (exec_command(node, env, status));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node, env, status));
	else if (node->type == NODE_REDIRECT_IN)
		return (exec_redirect_in(node, env, status));
	else if (node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_REDIRECT_APPEND)
		return (exec_redirect(node, env, status));
	else if (node->type == NODE_HEREDOC)
		return (exec_heredoc(node, env, status));
	return (1);
}

int	exec_ast(t_ast_node *node, t_map_str_str **env, int *status)
{
	get_all_heredoc_content(node);
	return (exec_node(node, env, status));
}
