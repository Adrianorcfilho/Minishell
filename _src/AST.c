#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tokenizer.h>
#include "AST.h"

t_ast_node *create_ast_node(t_node_type type)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->args = NULL;
    node->arg_count = 0;
    node->filename = NULL;
    node->heredoc_content = NULL;
    node->heredoc_delimiter = NULL;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

void add_arg_to_node(t_ast_node *node, char *arg)
{
    char **new_args;
    int i;

    new_args = malloc(sizeof(char *) * (node->arg_count + 2));
    if (!new_args)
        return ;

    i = 0;
    while (i < node->arg_count)
    {
        new_args[i] = node->args[i];
        i++;
    }
    new_args[i] = strdup(arg);
    new_args[i + 1] = NULL;

    if (node->args)
        free(node->args);
    node->args = new_args;
    node->arg_count++;

}

t_node_type token_type_to_node_type(t_token_type token_type)
{
    if (token_type == TOKEN_TYPE_REDIRECT_IN)
        return (NODE_REDIRECT_IN);
    if (token_type == TOKEN_TYPE_REDIRECT_OUT)
        return (NODE_REDIRECT_OUT);
    if (token_type == TOKEN_TYPE_REDIRECT_APPEND)
        return (NODE_REDIRECT_APPEND);
    if (token_type == TOKEN_TYPE_HEREDOC)
        return (NODE_HEREDOC);
    return (NODE_COMMAND);
}

// Parse commands,
// Need to handle things
//

t_ast_node *parse_simple_command(t_token **current)
{
    t_ast_node *cmd_node;
    t_ast_node *redirect_node;
    t_token *token;

    cmd_node = create_ast_node(NODE_COMMAND);
    if (!cmd_node)
        return (NULL);

    token = *current;

    while (token && token->type != TOKEN_TYPE_PIPE)
    {
        if (token->type == TOKEN_TYPE_WORD)
        {
            add_arg_to_node(cmd_node, token->value);
            token = token->next;
        }
        else if (token->type >= TOKEN_TYPE_REDIRECT_IN && token->type <= TOKEN_TYPE_HEREDOC)
        {
            redirect_node = create_ast_node(token_type_to_node_type(token->type));
            token = token->next;
            if (token && token->type == TOKEN_TYPE_WORD)
            {
                if (redirect_node->type == NODE_HEREDOC)
                    redirect_node->heredoc_delimiter = strdup(token->value);
                else
                    redirect_node->filename = strdup(token->value);
                redirect_node->left = cmd_node;
                cmd_node = redirect_node;
                token = token->next;
            }
            else
            {
                fprintf(stderr, "Error: no file after redirection");
                free(redirect_node);
                break ;
            }
        }
        else
            break ;
    }
    *current = token;
    return (cmd_node);
}

t_ast_node *parse_pipeline(t_token *tokens)
{
    t_ast_node *left;
    t_ast_node *pipe_node;
    t_token *current;

    if (!tokens)
        return (NULL);

    current = tokens;
    left = parse_simple_command(&current);

    while (current && current->type == TOKEN_TYPE_PIPE)
    {
        current = current->next;
        pipe_node = create_ast_node(NODE_PIPE);
        if (!pipe_node)
            return (left);
        pipe_node->left = left;
        pipe_node->right = parse_simple_command(&current);
        left = pipe_node;
    }
    return (left);
}

void free_ast(t_ast_node *node)
{
    int i;

    if (!node)
        return;
    if (node->args)
    {
        i = 0;
        while (i < node->arg_count)
        {
            free(node->args[i]);
            i++;
        }
        free(node->args);
    }
    if (node->filename)
        free(node->filename);
    if (node->heredoc_delimiter)
        free(node->heredoc_delimiter);
    if (node->heredoc_content)
        free(node->heredoc_content);
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
