/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:51:52 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/07 21:58:36 by adrocha-         ###   ########.fr       */
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

int	exec_redirect_in(t_ast_node *node, t_map_str_str **env, int *status)
{
	return (exec_redirect(node, env, status));
}

void	print_and_set_error(int *error, char *filename)
{
	perror(filename);
	*error = 1;
}

void	exe_redir_types(t_ast_node *redirs[1024], int i, int *error, int *fds)
{
	if (redirs[i]->type == NODE_REDIRECT_IN)
	{
		fds[i] = open(redirs[i]->filename, O_RDONLY);
		if (fds[i] == -1)
		{
			print_and_set_error(error, redirs[i]->filename);
		}
	}
	else if (redirs[i]->type == NODE_REDIRECT_OUT)
	{
		fds[i] = open(redirs[i]->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds[i] == -1)
		{
			print_and_set_error(error, redirs[i]->filename);
		}
	}
	else
	{
		fds[i] = open(redirs[i]->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds[i] == -1)
		{
			print_and_set_error(error, redirs[i]->filename);
		}
	}
}
