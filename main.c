#include "AST.h"
#include "tokenizer.h"
#include <mini_execution.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char		*prompt;
	t_token		*tokens;
	t_ast_node	*ast;

	// if (argc < 2)
	// {
	//     printf("Usage: %s <command>\n", argv[0]);
	//     return (1);
	// }
	// tokens = tokenize(argv[1]);
	while (1)
	{
		prompt = readline("🐚 ➤ ");
		if (!prompt)
			break ;
		if (*prompt == '\0')
		{
			free(prompt);
			continue ;
		}
		add_history(prompt);
		tokens = tokenize(prompt);
		ast = parse_pipeline(tokens);
		exec_ast(ast);
	}
	// printf("=== TOKENS ===\n");
	// display_tokens(tokens);
	// printf("\n=== AST ===\n");
	// ast = parse_pipeline(tokens);
	// display_ast(ast, 0);
	// printf("\n=== EXEC ===\n");
	// exec_ast(ast);
	free_tokens(tokens);
	free_ast(ast);
	return (0);
}
