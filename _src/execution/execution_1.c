/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:20 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 23:37:07 by adrocha-         ###   ########.fr       */
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

int	exec_redirect_in(t_ast_node *node, t_map_str_str **env, int *status)
{
	return (exec_redirect(node, env, status));
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
void	exe_redir_types(t_ast_node  *redirs[1024], int i, int *error, int *fds)
{
	if (redirs[i]->type == NODE_REDIRECT_IN)
	{
		fds[i] = open(redirs[i]->filename, O_RDONLY);
		if (fds[i] == -1)
		{
			perror(redirs[i]->filename);
			*error = 1;
		}
	}
	else if (redirs[i]->type == NODE_REDIRECT_OUT)
	{
		fds[i] = open(redirs[i]->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds[i] == -1)
		{
			perror(redirs[i]->filename);
			*error = 1;
		}
	}
	else
	{
		fds[i] = open(redirs[i]->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds[i] == -1)
		{
			perror(redirs[i]->filename);
			*error = 1;
		}
	}
}

int	exec_redirect(t_ast_node *node, t_map_str_str **env, int *status)
{
	t_ast_node	*redirs[1024];
	int			fds[1024];
	int			count;
	int			result;
	pid_t		pid;
	int			wstatus;
	t_ast_node	*curr;
	int			i;
	int			error;

	count = 0;
	curr = node;
	while (curr && (curr->type == NODE_REDIRECT_IN
			|| curr->type == NODE_REDIRECT_OUT
			|| curr->type == NODE_REDIRECT_APPEND))
	{
		redirs[count] = curr;
		fds[count] = -1;
		count++;
		curr = curr->left;
	}
	pid = safe_fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		error = 0;
		i = count - 1;
		while (i >= 0 && !error)
		{
			exe_redir_types(redirs, i, &error, fds);
			i--;
		}
		if (error)
		{
			i = 0;
			while (i < count)
			{
				if (fds[i] != -1)
					close(fds[i]);
				i++;
			}
			exit(1);
		}
		i = count - 1;
		while (i >= 0)
		{
			if (redirs[i]->type == NODE_REDIRECT_IN)
				dup2(fds[i], STDIN_FILENO);
			else
				dup2(fds[i], STDOUT_FILENO);
			close(fds[i]);
			i--;
		}
		result = exec_node(curr, env, status);
		exit(result);
	}
	waitpid(pid, &wstatus, 0);
	return (get_exit_status(wstatus));
}
