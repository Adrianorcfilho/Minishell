/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:38:37 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 02:21:08 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// minishell
#include "map.h"
#include <AST.h>
#include <execution.h>
#include <minilibft.h>
#include <readline/history.h>
#include <readline/readline.h>
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
	new_content = ft_realloc(content, total_len, total_len + line_len + 2);
	if (!new_content)
	{
		free(content);
		return (NULL);
	}
	ft_strcpy(new_content + total_len, line);
	new_content[total_len + line_len] = '\n';
	new_content[total_len + line_len + 1] = '\0';
	return (new_content);
}

static char	*read_heredoc_line(void)
{
	char	*line;

	line = readline("> ");
	return (line);
}

char	*get_heredoc_content(char *delimiter)
{
	char	*line;
	char	*content;
	size_t	total_len;

	content = NULL;
	total_len = 0;
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		content = append_line_to_content(content, line, total_len);
		if (!content)
			return (free(line), NULL);
		total_len += ft_strlen(line) + 1;
		free(line);
	}
	return (content);
}
