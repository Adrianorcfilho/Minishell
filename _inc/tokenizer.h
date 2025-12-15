/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:34:01 by ide-abre          #+#    #+#             */
/*   Updated: 2025/12/15 16:20:06 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
	TOKEN_TYPE_WORD,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_REDIRECT_IN,
	TOKEN_TYPE_REDIRECT_OUT,
	TOKEN_TYPE_REDIRECT_APPEND,
	TOKEN_TYPE_HEREDOC,
}					t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_MIXED
}					t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote_type;
	struct s_token	*next;
}					t_token;

t_token				*tokenize(char *prompt);
void				free_tokens(t_token *tokens);
void				display_tokens(t_token *tokens);
int					handle_special(char *input, int index, t_token **tokens);
void				link_tokens(t_token **tokens, t_token *new);
t_token				*create_token(t_token_type type, char *value);

#endif
