/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:12:13 by adrocha-          #+#    #+#             */
/*   Updated: 2025/12/04 23:12:17 by adrocha-         ###   ########.fr       */
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

char	*find_cmd_path(t_map_str_str *map, char *prog)
{
	char	*path;
	char	*candidate;
	char	**paths;
	char	**hold;

	path = map_get(map, "PATH");
	if (!path)
	    return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
	    return (NULL);
	hold = paths;
	while (*paths)
	{
		candidate = build_fullpath(*paths, prog);
		if (!candidate)
		{
			ft_free(hold);
			return (NULL);
		}
		if (access(candidate, X_OK) == 0)
		{
			ft_free(hold);
			return (candidate);
		}
		free(candidate);
		paths = paths + 1;
	}
	ft_free(hold);
	return (NULL);
}
