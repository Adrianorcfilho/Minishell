/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:38:37 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/27 00:47:30 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// minishell
#include "map.h"
#include <AST.h>
#include <execution.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*append_line_to_content(char *content, char *line, size_t total_len)
{
	size_t	line_len;
	char	*new_content;

	line_len = ft_strlen(line);
	new_content = ft_realloc(content, total_len + line_len + 2);
	if (!new_content)
		return (NULL);
	ft_strcpy(new_content + total_len, line);
	new_content[total_len + line_len] = '\n';
	new_content[total_len + line_len + 1] = '\0';
	return (new_content);
}

static char	*read_heredoc_line(char **line, size_t *len)
{
	ssize_t	read;

	write(STDOUT_FILENO, "> ", 2);
	read = getline(line, len, stdin);
	if (read == -1)
		return (NULL);
	if ((*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';
	return (*line);
}

char	*get_heredoc_content(char *delimiter)
{
	char	*line;
	char	*content;
	size_t	len;
	size_t	total_len;

	line = NULL;
	content = NULL;
	len = 0;
	total_len = 0;
	while (1)
	{
		if (!read_heredoc_line(&line, &len))
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		content = append_line_to_content(content, line, total_len);
		if (!content)
		{
			free(line);
			return (NULL);
		}
		total_len += ft_strlen(line) + 1;
	}
	free(line);
	return (content);
}
