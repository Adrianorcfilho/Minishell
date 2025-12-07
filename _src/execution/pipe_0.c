/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:12:45 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/28 15:04:04 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <AST.h>
#include <error_log.h>
#include <execution.h>
#include <fcntl.h>
#include <minilibft.h>
#include <permitions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	count_pipeline(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type != NODE_PIPE)
		return (1);
	return (count_pipeline(node->left) + count_pipeline(node->right));
}

void	collect_commands(t_ast_node *node, t_ast_node **cmds, int *idx)
{
	if (!node)
		return ;
	if (node->type != NODE_PIPE)
	{
		cmds[(*idx)++] = node;
		return ;
	}
	collect_commands(node->left, cmds, idx);
	collect_commands(node->right, cmds, idx);
}

int	exec_command_in_pipeline(t_cmd_exec *data)
{
	pid_t	pid;
	int		fd;

	pid = safe_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (data->input_fd != STDIN_FILENO)
		{
			dup2(data->input_fd, STDIN_FILENO);
			close(data->input_fd);
		}
		if (data->output_fd != STDOUT_FILENO)
		{
			dup2(data->output_fd, STDOUT_FILENO);
			close(data->output_fd);
		}
		fd = 3;
		while (fd < 256)
		{
			close(fd);
			fd++;
		}
		exit(exec_node(data->cmd, data->env, data->status));
	}
	return (pid);
}

void	close_and_update_fd(t_fd_info *info)
{
	if (*info->input_fd != STDIN_FILENO)
		close(*info->input_fd);
	if (info->i < info->count - 1)
	{
		close(info->fd[1]);
		*info->input_fd = info->fd[0];
	}
}

int	wait_all_processes(pid_t *pids, int count)
{
	int		i;
	int		exit_status;
	int		last_status;
		int status;
	pid_t	finished;

	last_status = 0;
	i = 0;
	while (i < count)
	{
		finished = waitpid(-1, &status, 0);
		if (finished == pids[count - 1])
			last_status = get_exit_status(status);
		i++;
	}
	return (last_status);
}
