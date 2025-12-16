/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:04 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 03:21:17 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <errno.h>
#include <map.h>
#include <minilibft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
int	builtin_cd(t_ast_node *node, t_map_str_str **env)
{
	char	*path;

	if (node->arg_count > 2)
	{
		ft_putstr_fd(stderr, "cd: too many arguments\n");
		return (1);
	}
	if (node->args[1])
		path = node->args[1];
	else
		path = map_get(*env, "HOME");
	if (!path)
	{
		ft_putstr_fd(stderr, "cd: HOME not set\n");
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
		if (ft_strcmp(node->args[1], "-") == 0)
		{
			*path = map_get(*env, "OLDPWD");
			if (!(*path))
				return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 0);
			printf("%s\n", *path);
		}
		else
			*path = node->args[1];
	}
	else
		*path = map_get(*env, "HOME");
	return (1);
}

static void	get_old_pwd(char *old_pwd, t_map_str_str **env)
{
	char	*saved_oldpwd;

	saved_oldpwd = map_get(*env, "PWD");
	if (!saved_oldpwd)
		saved_oldpwd = "";
	if (getcwd(old_pwd, PATH_MAX) == NULL)
	{
		ft_strncpy(old_pwd, saved_oldpwd, PATH_MAX - 1);
		old_pwd[PATH_MAX - 1] = '\0';
	}
}

static void	construct_relative_path(char *new_pwd, char *old_pwd, char *path)
{
	size_t	len;

	len = ft_strlen(old_pwd);
	if (len > 0 && len < PATH_MAX - 2)
	{
		ft_strncpy(new_pwd, old_pwd, PATH_MAX - 1);
		if (new_pwd[len - 1] != '/')
			ft_strncat(new_pwd, "/", PATH_MAX - len - 1);
		ft_strncat(new_pwd, path, PATH_MAX - ft_strlen(new_pwd) - 1);
		new_pwd[PATH_MAX - 1] = '\0';
	}
}

static void	update_pwd_vars(t_map_str_str **env, char *old_pwd, char *new_pwd,
		char *path)
{
	map_set(env, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, PATH_MAX) != NULL)
		map_set(env, "PWD", new_pwd);
	else if (path[0] == '/')
		map_set(env, "PWD", path);
	else
	{
		construct_relative_path(new_pwd, old_pwd, path);
		if (ft_strlen(new_pwd) > 0)
			map_set(env, "PWD", new_pwd);
		else
			map_set(env, "PWD", path);
	}
}

int	builtin_cd(t_ast_node *node, t_map_str_str **env, t_global_vars *vars)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (node->arg_count > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	get_old_pwd(old_pwd, env);
	if (check_old_path(node, env, &path) == 0)
		return (1);
	if (!path)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	if (chdir(path) == -1)
		return (perror("cd"), 1);
	update_pwd_vars(env, old_pwd, new_pwd, path);
	if (vars->const_pwd)
		free(vars->const_pwd);
	vars->const_pwd = ft_strdup(map_get(*env, "PWD"));
	return (0);
}
