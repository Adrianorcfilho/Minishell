/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:12:13 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/15 15:56:32 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <unistd.h>

static char	*build_fullpath(char *path, const char *cmd)
{
	char	*abs;

	if (!path || !cmd)
		return (NULL);
	abs = ft_strjoin(path, "/");
	abs = ft_strjoin(abs, cmd);
	return (abs);
}

static char	*try_path(char *dir, char *prog)
{
	char	*candidate;

	candidate = build_fullpath(dir, prog);
	if (!candidate)
		return (NULL);
	if (access(candidate, X_OK) == 0)
		return (candidate);
	free(candidate);
	return (NULL);
}

char	*find_cmd_path(t_map_str_str *map, char *prog)
{
	char	*path;
	char	*result;
	char	**paths;
	int		i;

	path = map_get(map, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		result = try_path(paths[i], prog);
		if (result)
		{
			ft_free(paths);
			return (result);
		}
	}
	ft_free(paths);
	return (NULL);
}
