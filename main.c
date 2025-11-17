#include "tokenizer.h"
#include "AST.h"

#include <mini_execution.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    t_token *tokens;
    t_ast_node *ast;

    if (argc < 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        return (1);
    }

    tokens = tokenize(argv[1]);

    printf("=== TOKENS ===\n");
    display_tokens(tokens);

    printf("\n=== AST ===\n");
    ast = parse_pipeline(tokens);
    display_ast(ast, 0);

    printf("\n=== EXEC ===\n");
    exec_ast(ast);

    free_tokens(tokens);
    free_ast(ast);
    return (0);
}
