/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:38:37 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 02:44:39 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <AST.h>
#include <execution.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	setup_heredoc_pipe(t_ast_node *node, int *pipefd)
{
	if (!node->heredoc_content)
	{
		ft_putstr_fd("Error: heredoc content not available\n", 2);
		return (-1);
	}
	if (!node->left || node->left->type != NODE_COMMAND)
	{
		ft_putstr_fd("Error: invalid heredoc structure\n", 2);
		return (-1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	exec_heredoc(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *exit_status)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		result;

	if (setup_heredoc_pipe(node, pipefd) == -1)
		return (1);
	pid = safe_fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), 1);
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		result = exec_node(node->left, env, vars, exit_status);
		cleanup_and_exit(vars, env, result);
	}
	close(pipefd[0]);
	write(pipefd[1], node->heredoc_content, ft_strlen(node->heredoc_content));
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

void	get_all_heredoc_content(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_HEREDOC)
		node->heredoc_content = get_heredoc_content(node->heredoc_delimiter);
	get_all_heredoc_content(node->left);
	get_all_heredoc_content(node->right);
}
