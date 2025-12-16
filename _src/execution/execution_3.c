/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:05:20 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/16 03:12:12 by ide-abre         ###   ########.fr       */
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
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

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

int	exec_node(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *status)
{
	if (!node)
		return (-1);
	if (node->type == NODE_COMMAND)
		return (exec_command(node, env, vars, status));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node, env, vars, status));
	else if (node->type == NODE_REDIRECT_IN)
		return (exec_redirect_in(node, env, vars, status));
	else if (node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_REDIRECT_APPEND)
		return (exec_redirect(node, env, vars, status));
	else if (node->type == NODE_HEREDOC)
		return (exec_heredoc(node, env, vars, status));
	return (1);
}

int	exec_ast(t_ast_node *node, t_map_str_str **env, t_global_vars *vars,
		int *status)
{
	get_all_heredoc_content(node);
	return (exec_node(node, env, vars, status));
}
