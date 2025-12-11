/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:20 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/11 23:18:21 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <AST.h>
#include <error_log.h>
#include <execution.h>
#include <fcntl.h>
#include <map.h>
#include <minilibft.h>
#include <permitions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int	setup_input_redirect(t_ast_node *node)
{
	int	fd;

	if (!node->filename)
	{
		fprintf(stderr, "Missing file name for redirection\n");
		return (-1);
	}
	if (!node->left)
	{
		fprintf(stderr, "Invalid redirect structure\n");
		return (-1);
	}
	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(node->filename);
		return (-1);
	}
	return (fd);
}

static int	setup_output_redirect(t_ast_node *node)
{
	int	fd;

	if (!node->filename)
	{
		fprintf(stderr, MISSING_FILE_FOR_DIRECTION);
		return (-1);
	}
	if (!node->left)
	{
		fprintf(stderr, INVALID_STRUCTURE_FOR_DIRECTION);
		return (-1);
	}
	fd = safe_open(node->type, node->filename);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	create_dup2_error(t_ast_node *redirs[1024], int fds[1024], int count,
		int *i)
{
	int	error;

	error = 0;
	while (*i >= 0 && !error)
	{
		exe_redir_types(redirs, *i, &error, fds);
		(*i)--;
	}
	if (error)
	{
		*i = 0;
		while (*i < count)
		{
			if (fds[*i] != -1)
				close(fds[*i]);
			(*i)++;
		}
		exit(1);
	}
}

void	create_dup2(t_create_dup2_var_list d_list, t_map_str_str **env,
		t_global_vars *vars, int *status)
{
	int	result;
	int	i;

	i = d_list.count - 1;
	create_dup2_error(d_list.redirs, d_list.fds, d_list.count, &i);
	i = d_list.count - 1;
	while (i >= 0)
	{
		if (d_list.redirs[i]->type == NODE_REDIRECT_IN)
			dup2(d_list.fds[i], STDIN_FILENO);
		else
			dup2(d_list.fds[i], STDOUT_FILENO);
		close(d_list.fds[i]);
		i--;
	}
	result = exec_node(d_list.curr, env, vars, status);
	exit(result);
}

int	exec_redirect(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *status)
{
	t_ast_node				*redirs[1024];
	int						fds[1024];
	t_exe_redir_var_list	v_list;
	t_ast_node				*curr;

	v_list.count = 0;
	curr = node;
	while (curr && (curr->type == NODE_REDIRECT_IN
			|| curr->type == NODE_REDIRECT_OUT
			|| curr->type == NODE_REDIRECT_APPEND))
	{
		redirs[v_list.count] = curr;
		fds[v_list.count] = -1;
		v_list.count++;
		curr = curr->left;
	}
	v_list.pid = safe_fork();
	if (v_list.pid == -1)
		return (1);
	if (v_list.pid == 0)
		create_dup2((t_create_dup2_var_list){redirs, fds, v_list.count, curr},
			env, vars, status);
	waitpid(v_list.pid, &v_list.wstatus, 0);
	return (get_exit_status(v_list.wstatus));
}
