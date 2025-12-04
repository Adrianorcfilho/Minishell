// #include <AST.h>
// #include <execution.h>
// #include <expander.h>
// #include <map.h>
// #include <minilibft.h>
// #include <readline/history.h>
// #include <readline/readline.h>
// #include <stdlib.h>
// #include <tokenizer.h>
// #include <signals.h>
// #include <signal.h>
// #include <stdio.h>

// extern volatile sig_atomic_t g_signal_received;

// static void debug_print_tokens(t_token *tokens)
// {
//     t_token *debug_tok = tokens;
//     int count = 0;
    
//     printf("\n=== TOKENS ===\n");
//     while (debug_tok)
//     {
//         printf("[%d] Type: %d, Value: '%s'\n", count++, debug_tok->type, debug_tok->value);
//         debug_tok = debug_tok->next;
//     }
//     printf("==============\n\n");
// }

// static void debug_print_ast(t_ast_node *ast, int depth)
// {
//     int i;
    
//     if (!ast)
//         return;
    
//     for (i = 0; i < depth; i++)
//         printf("  ");
    
//     printf("Node type: %d", ast->type);
    
//     if (ast->type == NODE_COMMAND && ast->args)
//     {
//         printf(" Args: [");
//         for (i = 0; i < ast->arg_count; i++)
//         {
//             printf("'%s'", ast->args[i]);
//             if (i < ast->arg_count - 1)
//                 printf(", ");
//         }
//         printf("]");
//     }
    
//     if (ast->filename)
//         printf(" Filename: '%s'", ast->filename);
    
//     if (ast->heredoc_delimiter)
//         printf(" Heredoc delimiter: '%s'", ast->heredoc_delimiter);
    
//     printf("\n");
    
//     if (ast->left)
//     {
//         for (i = 0; i < depth; i++)
//             printf("  ");
//         printf("Left:\n");
//         debug_print_ast(ast->left, depth + 1);
//     }
    
//     if (ast->right)
//     {
//         for (i = 0; i < depth; i++)
//             printf("  ");
//         printf("Right:\n");
//         debug_print_ast(ast->right, depth + 1);
//     }
// }

// static int process_input_debug(char *prompt, t_map_str_str **map_env,
//     int last_status)
// {
//     char        *expanded;
//     t_token     *tokens;
//     t_ast_node  *ast;
    
//     printf("\n========================================\n");
//     printf("Input: '%s'\n", prompt);
//     printf("========================================\n");
    
//     expanded = expand_variables(prompt, *map_env, last_status);
//     printf("Expanded: '%s'\n", expanded);
    
//     add_history(prompt);
//     tokens = tokenize(expanded);
    
//     debug_print_tokens(tokens);
    
//     ast = parse_pipeline(tokens);
    
//     if (!ast)
//     {
//         printf("❌ Parser returned NULL\n");
//         free(expanded);
//         free_tokens(tokens);
//         return (2);
//     }
    
//     printf("=== AST ===\n");
//     debug_print_ast(ast, 0);
//     printf("===========\n\n");
    
//     if (validate_syntax(ast))
//     {
//         printf("❌ Syntax validation failed\n");
//         free(expanded);
//         free_tokens(tokens);
//         free_ast(ast);
//         return (2);
//     }
    
//     printf("✅ Parsing successful!\n");
//     printf("Executing...\n\n");
    
//     last_status = exec_ast(ast, map_env, &last_status);
    
//     free(expanded);
//     free_tokens(tokens);
//     free_ast(ast);
//     return (last_status);
// }

// static void run_tests(t_map_str_str *map_env)
// {
//     char *test_cases[] = {
//         "echo hello",
//         "echo hello world",
//         "grep hi < minishell_tester/test_files/infile",
//         "cat < minishell_tester/test_files/infile",
//         "echo hi < minishell_tester/test_files/infile bye bye",
//         "ls > outfile.txt",
//         "cat <\"./test_files/infile\"",
//         "echo \"$\"",
//         "echo '$'",
//         NULL
//     };
//     int i = 0;
//     int last_status = 0;
    
//     printf("\n");
//     printf("╔════════════════════════════════════════════════════════════╗\n");
//     printf("║          MINISHELL DEBUG TEST SUITE                       ║\n");
//     printf("╚════════════════════════════════════════════════════════════╝\n");
    
//     while (test_cases[i])
//     {
//         printf("\n\n");
//         printf("┌────────────────────────────────────────────────────────────┐\n");
//         printf("│ TEST %d                                                    │\n", i + 1);
//         printf("└────────────────────────────────────────────────────────────┘\n");
        
//         last_status = process_input_debug(test_cases[i], &map_env, last_status);
        
//         printf("Exit status: %d\n", last_status);
//         i++;
//     }
    
//     printf("\n\n");
//     printf("╔════════════════════════════════════════════════════════════╗\n");
//     printf("║          TEST SUITE COMPLETE                               ║\n");
//     printf("╚════════════════════════════════════════════════════════════╝\n");
// }

// int main(int argc, char **argv, char **env)
// {
//     char            *prompt;
//     t_map_str_str   *map_env;
//     int             last_status;
//     int             test_mode = 0;
    
//     // Check if we're in test mode
//     if (argc > 1 && ft_strcmp(argv[1], "--test") == 0)
//         test_mode = 1;
    
//     last_status = 0;
//     map_env = env_init(env);
    
//     if (test_mode)
//     {
//         run_tests(map_env);
//         free_map(map_env);
//         return (0);
//     }
    
//     setup_signals();
//     while (1)
//     {
//         prompt = readline("🐚 ➤ ");
//         if (!prompt)
//             break ;
//         if (*prompt == '\0')
//         {
//             free(prompt);
//             continue ;
//         }
//         if (g_signal_received == SIGINT)
//         {
//             last_status = 130;
//             g_signal_received = 0;
//         }
//         last_status = process_input_debug(prompt, &map_env, last_status);
//         free(prompt);
//     }
//     free_map(map_env);
//     rl_clear_history();
//     return (last_status);
// }