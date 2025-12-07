/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:49:18 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 23:06:30 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	setup_pipe_fds(int *fd, int *output_fd, int i, int count)
{
	if (i < count - 1)
	{
		pipe(fd);
		*output_fd = fd[1];
	}
	else
		*output_fd = STDOUT_FILENO;
}

int	execute_commands_loop(t_pipeline *pipeline, pid_t *pids)
{
	int			i;
	int			fd[2];
	int			input_fd;
	int			output_fd;
	t_cmd_exec	cmd_data;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < pipeline->count)
	{
		if (i < pipeline->count - 1)
		{
			if (pipe(fd) == -1)
				return (-1);
			output_fd = fd[1];
		}
		else
			output_fd = STDOUT_FILENO;
		cmd_data = (t_cmd_exec){pipeline->cmds[i], pipeline->env,
			pipeline->status, input_fd, output_fd};
		pids[i] = exec_command_in_pipeline(&cmd_data);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (i < pipeline->count - 1)
			input_fd = fd[0];
		i++;
	}
	return (0);
}

int	exec_pipeline_commands(t_pipeline *pipeline)
{
	pid_t	*pids;
	int		result;

	pids = malloc(sizeof(pid_t) * pipeline->count);
	if (!pids)
		return (-1);
	execute_commands_loop(pipeline, pids);
	result = wait_all_processes(pids, pipeline->count);
	free(pids);
	return (result);
}

int	exec_pipe(t_ast_node *node, t_map_str_str **env, int *status)
{
	t_ast_node **cmds;
	int count;
	int idx;
	int result;
	t_pipeline pipeline;

	count = count_pipeline(node);
	cmds = malloc(sizeof(t_ast_node *) * count);
	if (!cmds)
		return (-1);
	idx = 0;
	collect_commands(node, cmds, &idx);
	pipeline = (t_pipeline){cmds, count, env, status};
	result = exec_pipeline_commands(&pipeline);
	free(cmds);
	return (result);
}