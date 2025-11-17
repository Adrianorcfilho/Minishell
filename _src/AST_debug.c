#include "AST.h"
#include <stdio.h>

void display_ast(t_ast_node *node, int depth)
{
    int i;

    if (!node)
        return;

    for (i = 0; i < depth; i++)
        printf("  ");

    if (node->type == NODE_COMMAND)
    {
        printf("COMMAND: ");
        i = 0;
        while (i < node->arg_count)
        {
            printf("%s ", node->args[i]);
            i++;
        }
        printf("\n");
    }
    else if (node->type == NODE_PIPE)
    {
        printf("PIPE\n");
        display_ast(node->left, depth + 1);
        display_ast(node->right, depth + 1);
    }
    else if (node->type == NODE_REDIRECT_IN)
    {
        printf("REDIRECT_IN: %s\n", node->filename);
        display_ast(node->left, depth + 1);
    }
    else if (node->type == NODE_REDIRECT_OUT)
    {
        printf("REDIRECT_OUT: %s\n", node->filename);
        display_ast(node->left, depth + 1);
    }
    else if (node->type == NODE_REDIRECT_APPEND)
    {
        printf("REDIRECT_APPEND: %s\n", node->filename);
        display_ast(node->left, depth + 1);
    }
    else if (node->type == NODE_HEREDOC)
    {
        printf("HEREDOC: %s\n", node->filename);
        display_ast(node->left, depth + 1);
    }
}
