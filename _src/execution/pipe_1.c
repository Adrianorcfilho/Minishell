/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:49:18 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/11 23:07:18 by adrocha-         ###   ########.fr       */
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

void	exec_cmd_loop_close(t_io_fd *io, int i, int fd[2], int count)
{
	if (io->output_fd != STDOUT_FILENO)
		close(io->output_fd);
	if (io->input_fd != STDIN_FILENO)
		close(io->input_fd);
	if (i < count - 1)
		io->input_fd = fd[0];
}

int	execute_commands_loop(t_pipeline *pipeline, pid_t *pids,
		t_global_vars *vars)
{
	int			i;
	int			fd[2];
	t_io_fd		io;
	t_cmd_exec	cmd_data;

	io.input_fd = STDIN_FILENO;
	i = 0;
	while (i < pipeline->count)
	{
		if (i < pipeline->count - 1)
		{
			if (pipe(fd) == -1)
				return (-1);
			io.output_fd = fd[1];
		}
		else
			io.output_fd = STDOUT_FILENO;
		cmd_data = (t_cmd_exec){pipeline->cmds[i], pipeline->env,
			pipeline->status, io.input_fd, io.output_fd};
		pids[i] = exec_command_in_pipeline(&cmd_data, vars);
		exec_cmd_loop_close(&io, i, fd, pipeline->count);
		i++;
	}
	return (0);
}

int	exec_pipeline_commands(t_pipeline *pipeline, t_global_vars *vars)
{
	pid_t	*pids;
	int		result;

	pids = malloc(sizeof(pid_t) * pipeline->count);
	if (!pids)
		return (-1);
	execute_commands_loop(pipeline, pids, vars);
	result = wait_all_processes(pids, pipeline->count);
	free(pids);
	return (result);
}

int	exec_pipe(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *status)
{
	t_ast_node	**cmds;
	int			count;
	int			idx;
	int			result;
	t_pipeline	pipeline;

	count = count_pipeline(node);
	cmds = malloc(sizeof(t_ast_node *) * count);
	if (!cmds)
		return (-1);
	idx = 0;
	collect_commands(node, cmds, &idx);
	pipeline = (t_pipeline){cmds, count, env, status};
	result = exec_pipeline_commands(&pipeline, vars);
	free(cmds);
	return (result);
}
