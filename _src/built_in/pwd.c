/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:12 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/13 21:45:38 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <stdio.h>
#include <unistd.h>

int	builtin_pwd(t_map_str_str **env, t_global_vars *vars)
{
	char	cwd[4096];

	(void)env;
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		if (!vars->const_pwd)
		{
			perror("pwd");
			return (1);
		}
		printf("%s\n", vars->const_pwd);
	}
	return (1);
}
