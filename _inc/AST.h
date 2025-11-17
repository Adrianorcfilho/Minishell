#ifndef AST_H
#define AST_H

#include "tokenizer.h"

typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIRECT_IN,     //
    NODE_REDIRECT_OUT,    // >
    NODE_REDIRECT_APPEND, // >>
    NODE_HEREDOC,         // <<
}   t_node_type;

typedef struct s_ast_node
{
    t_node_type type;
    char **args;
    int arg_count;
    char *filename;
    char *heredoc_delimiter;
    char *heredoc_content;
    struct s_ast_node *left;
    struct s_ast_node *right;
}  t_ast_node;

t_ast_node *parse_pipeline(t_token *tokens);

// Debug functions
void    display_ast(t_ast_node *node, int depth);
void    free_ast(t_ast_node *node);

#endif
