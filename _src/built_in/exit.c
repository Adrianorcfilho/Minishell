/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:29:59 by ide-abre          #+#    #+#             */
/*   Updated: 2025/11/27 10:44:53 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <map.h>

#include <minilibft.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static int is_numeric_argument(const char *s)
{
    int i = 0;

    if (!s)
        return (0);

    // optional + or -
    if (s[i] == '+' || s[i] == '-')
        i++;

    if (!ft_isdigit(s[i]))
        return (0);

    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}

static long long	ft_atoll(const char *s)
{
    long long   res = 0;
    long long   sign = 1;

    if (*s == '-' || *s == '+')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }
    while (*s && ft_isdigit(*s))
    {
        res = res * 10 + (*s - '0');
        s++;
    }
    return (res * sign);
}

int	builtin_exit(t_ast_node *node, t_map_str_str **env, int *exit_status)
{
    long long   code;

    (void)env; // unused, but keep prototype consistent

    printf("exit\n");

    // no arguments: exit with previous status
    if (node->arg_count == 1)
        exit(*exit_status);

    // first argument is NOT numeric
    if (!is_numeric_argument(node->args[1]))
    {
        fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
                node->args[1]);
        exit(2);
    }

    // too many arguments
    if (node->arg_count > 2)
    {
        fprintf(stderr, "minishell: exit: too many arguments\n");
        return (1);    // DO NOT EXIT
    }

    // convert safely
    code = ft_atoll(node->args[1]);

    // wrap around the exit code
    code = (unsigned char)code;

    exit(code);
}


