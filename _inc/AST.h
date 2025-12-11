/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrocha- <adrocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:33:37 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/11 23:14:19 by adrocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define TK_TYPE_TO_ND_TYPE token_type_to_node_type

# include "tokenizer.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_HEREDOC,
}						t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	int					arg_count;
	char				*filename;
	char				*heredoc_delimiter;
	char				*heredoc_content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

// Debug functions
void					display_ast(t_ast_node *node, int depth);
void					free_ast(t_ast_node *node);
void					add_arg_to_node(t_ast_node *node, char *arg);
t_ast_node				*create_ast_node(t_node_type type);
t_node_type				token_type_to_node_type(t_token_type token_type);
t_ast_node				*parse_simple_command(t_token **current);
t_ast_node				*parse_pipeline(t_token *tokens);
int						validate_syntax(t_ast_node *node);

#endif
