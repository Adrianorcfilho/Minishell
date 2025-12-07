/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:28 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/25 09:35:04 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}
