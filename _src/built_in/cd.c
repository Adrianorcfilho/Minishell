/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:04 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/12 22:29:12 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <errno.h>
#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
int	builtin_cd(t_ast_node *node, t_map_str_str **env)
{
	char	*path;

	if (node->arg_count > 2)
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	if (node->args[1])
		path = node->args[1];
	else
		path = map_get(*env, "HOME");
	if (!path)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
*/

#define PATH_MAX 4096

int	check_old_path(t_ast_node *node, t_map_str_str **env, char **path)
{
	if (node->args[1])
	{
		if (strcmp(node->args[1], "-") == 0)
		{
			*path = map_get(*env, "OLDPWD");
			if (!(*path))
				return (fprintf(stderr, "cd: OLDPWD not set\n"), 0);
			printf("%s\n", *path);
		}
		else
			*path = node->args[1];
	}
	else
		*path = map_get(*env, "HOME");
	return (1);
}

int	builtin_cd(t_ast_node *node, t_map_str_str **env, t_global_vars *vars)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (node->arg_count > 2)
		return (fprintf(stderr, "cd: too many arguments\n"), 1);
	if (getcwd(old_pwd, PATH_MAX) == NULL)
	{
		if (check_old_path(node, env, &path))
		{
			if (chdir(path) == -1)
			{
				return (perror("cd"), 1);
			}
		}
		return (1);
	}
	if (check_old_path(node, env, &path) == 0)
		return (1);
	if (!path)
		return (fprintf(stderr, "cd: HOME not set\n"), 1);
	if (chdir(path) == -1)
		return (perror("cd"), 1);
	if (getcwd(new_pwd, PATH_MAX) != NULL)
	{
		map_set(env, "OLDPWD", old_pwd);
		map_set(env, "PWD", new_pwd);
		vars->const_pwd = new_pwd;
	}
	return (0);
}
