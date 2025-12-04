/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:58:22 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/04 22:49:50 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTE: This structure is assumed based on common shell implementations.
// You may need to adjust based on your actual t_ast_node definition.
/*
typedef struct s_ast_node
{
    // ... other members
    t_list_str *args; // A linked list of strings (the arguments)
    // ... other members
} t_ast_node;
*/

// A basic structure for a linked list of strings (arguments)

#include <AST.h>
#include <stdio.h>
#include <string.h>
#include <map.h>

int builtin_echo(t_ast_node *node, t_map_str_str *env)
{
    int i;
    int has_n_flag; // 1 if '-n' is present, 0 otherwise

    // Suppress unused variable warning for 'env'
    (void)env; 

    // Handle the case where there are no arguments (i.e., just the command name)
    if (!node || node->arg_count == 0)
        return (printf("\n"), 0);

    // 1. Check for the '-n' flag
    has_n_flag = 0;
    
    // Check if the very first argument is the '-n' flag
    if (node->arg_count > 0 && strcmp(node->args[0], "-n") == 0)
    {
        has_n_flag = 1;
        i = 1; // Start printing from the second argument
    }
    else
    {
        i = 0; // Start printing from the first argument
    }

    // 2. Print all remaining arguments separated by a space
    while (i < node->arg_count)
    {
        // Print the current argument
        printf("%s", node->args[i]);

        // Print a space *after* the argument, unless it's the last one
        if (i < node->arg_count - 1)
            printf(" "); 

        i++;
    }

    // 3. Print a newline unless the '-n' flag was present
    if (has_n_flag == 0)
        printf("\n");

    return (0);
}