/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:36:36 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/16 22:07:22 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AST.h>
#include <execution.h>
#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <signals.h>
#include <stdlib.h>
#include <tokenizer.h>

extern volatile sig_atomic_t	g_signal_received;

static int	process_input(char *prompt, t_map_str_str **map_env,
		t_global_vars *vars, int last_status)
{
	t_token		*tokens;
	t_ast_node	*ast;

	add_history(prompt);
	tokens = tokenize(prompt);
	if (!tokens)
		return (last_status);
	expand_tokens(tokens, *map_env, last_status);
	ast = parse_pipeline(tokens);
	vars->current_tokens = tokens;
	vars->current_ast = ast;
	if (!ast || validate_syntax(ast))
	{
		free_tokens(tokens);
		free_ast(ast);
		vars->current_tokens = NULL;
		vars->current_ast = NULL;
		return (2);
	}
	last_status = exec_ast(ast, map_env, vars, &last_status);
	free_tokens(tokens);
	free_ast(ast);
	vars->current_tokens = NULL;
	vars->current_ast = NULL;
	return (last_status);
}

static int	handle_signal_status(int last_status)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		return (130);
	}
	return (last_status);
}

static int	handle_prompt(char *prompt, t_map_str_str **map_env,
		t_global_vars *vars, int last_status)
{
	if (*prompt == '\0')
	{
		free(prompt);
		return (last_status);
	}
	last_status = handle_signal_status(last_status);
	last_status = process_input(prompt, map_env, vars, last_status);
	free(prompt);
	return (last_status);
}

static int	cleanup_shell(t_map_str_str *map_env, t_global_vars *vars,
		int last_status)
{
	if (vars->current_ast)
		free_ast(vars->current_ast);
	if (vars->current_tokens)
		free_tokens(vars->current_tokens);
	free_map(map_env);
	if (vars->const_pwd)
		free(vars->const_pwd);
	vars->current_ast = NULL;
	vars->current_tokens = NULL;
	vars->const_pwd = NULL;
	rl_clear_history();
	return (last_status);
}

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_map_str_str	*map_env;
	t_global_vars	vars;
	int				last_status;

	(void)argc;
	(void)argv;
	vars.const_pwd = NULL;
	vars.current_tokens = NULL;
	vars.current_ast = NULL;
	last_status = 0;
	map_env = env_init(env, &vars);
	setup_signals();
	while (1)
	{
		prompt = readline("🐚 ➤ ");
		if (!prompt)
			break ;
		last_status = handle_prompt(prompt, &map_env, &vars, last_status);
	}
	cleanup_shell(map_env, &vars, last_status);
	return (0);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_map_str_str	*map_env;
	char			**arr;

	map_env = env_init(env);
	arr = map_as_c_array(map_env);
	ft_free(arr);
	free_map(map_env);
	return (0);
}
*/

/*
static int	process_input_no_history(char *prompt, t_map_str_str **map_env,
		int last_status)
{
	char		*expanded;
	t_token		*tokens;
	t_ast_node	*ast;

	expanded = expand_variables(prompt, *map_env, last_status);
	tokens = tokenize(expanded);
	ast = parse_pipeline(tokens);
	last_status = exec_ast(ast, map_env, &last_status);
	free(expanded);
	free_tokens(tokens);
	free_ast(ast);
	return (last_status);
}

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_map_str_str	*map_env;
	int				last_status;
	int				test_count;

	(void)argc;
	(void)argv;
	last_status = 0;
	map_env = env_init(env);
	if (!map_env)
		return (1);
	test_count = 0;
	while (test_count < 1)
	{
		prompt = ft_strdup("echo test");
		if (!prompt)
			break ;
		if (*prompt == '\0')
		{
			free(prompt);
			continue ;
		}
		last_status = process_input_no_history(prompt, &map_env, last_status);
		free(prompt);
		test_count++;
	}
	free_map(map_env);
	rl_clear_history();
	return (last_status);
}
*/

/* main
int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_token			*tokens;
	t_ast_node		*ast;
	t_map_str_str	*map_env;
	char			*expanded;
	int				last_status;

	last_status = 0;
	map_env = env_init(env);
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
		expanded = expand_variables(prompt, map_env, last_status);
		// printf("EXP: %s\n", expanded);
		add_history(prompt);
		tokens = tokenize(expanded);
		ast = parse_pipeline(tokens);
		last_status = exec_ast(ast, &map_env, &last_status);
		// printf("=== TOKENS ===\n");
		// display_tokens(tokens);
		// printf("\n=== AST ===\n");
		// ast = parse_pipeline(tokens);
		// display_ast(ast, 0);
		// printf("\n=== EXEC ===\n");
		// exec_ast(ast);
		free(prompt);
		free(expanded);
		free_tokens(tokens);
		free_ast(ast);
	}
	// map free
	return (last_status);
}
*/
