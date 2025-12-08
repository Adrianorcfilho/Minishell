/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:36:36 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/07 23:41:15 by adrocha-         ###   ########.fr       */
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

char	*remove_outer_quotes(char *str)
{
	char	*result;
	char	in_quote;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = str[i];
			i++;
			continue ;
		}
		if (in_quote && str[i] == in_quote)
		{
			in_quote = 0;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	expand_tokens(t_token *tokens, t_map_str_str *map_env, int last_status)
{
	t_token	*current;
	char	*expanded;
	char	*unquoted;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_TYPE_WORD)
		{
			expanded = expand_variables(current->value, map_env, last_status);
			unquoted = remove_outer_quotes(expanded);
			free(current->value);
			free(expanded);
			current->value = unquoted;
		}
		current = current->next;
	}
}

static int	process_input(char *prompt, t_map_str_str **map_env,
		int last_status)
{
	t_token		*tokens;
	t_ast_node	*ast;

	add_history(prompt);
	tokens = tokenize(prompt);
	expand_tokens(tokens, *map_env, last_status);
	ast = parse_pipeline(tokens);
	if (!ast || validate_syntax(ast))
	{
		free_tokens(tokens);
		free_ast(ast);
		return (2);
	}
	last_status = exec_ast(ast, map_env, &last_status);
	free_tokens(tokens);
	free_ast(ast);
	return (last_status);
}

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_map_str_str	*map_env;
	int				last_status;

	last_status = 0;
	map_env = env_init(env);
	setup_signals();
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
		if (g_signal_received == SIGINT)
		{
			last_status = 130;
			g_signal_received = 0;
		}
		last_status = process_input(prompt, &map_env, last_status);
		free(prompt);
	}
	free_map(map_env);
	rl_clear_history();
	return (last_status);
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
