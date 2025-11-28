/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:04 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/28 15:00:42 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <map.h>
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <minilibft.h>
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

int builtin_cd(t_ast_node *node, t_map_str_str **env)
{
    char    *path;
    char    old_pwd[PATH_MAX];
    char    new_pwd[PATH_MAX];

    if (node->arg_count > 2)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return (1);
    }
    if (getcwd(old_pwd, PATH_MAX) == NULL)
    {
        perror("cd: getcwd");
        return (1);
    }
    if (node->args[1])
    {
        if (strcmp(node->args[1], "-") == 0)
        {
            path = map_get(*env, "OLDPWD");
            if (!path)
            {
                fprintf(stderr, "cd: OLDPWD not set\n");
                return (1);
            }
            printf("%s\n", path);
        }
        else
            path = node->args[1];
    }
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
    if (getcwd(new_pwd, PATH_MAX) != NULL)
    {
        map_set(env, "OLDPWD", old_pwd);
        map_set(env, "PWD", new_pwd);
    }
    return (0);
}
