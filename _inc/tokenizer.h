#ifndef TOKENIZER_H
#define TOKENIZER_H


typedef enum e_token_type
{
    TOKEN_TYPE_WORD,
    TOKEN_TYPE_PIPE,
    TOKEN_TYPE_REDIRECT_IN,
    TOKEN_TYPE_REDIRECT_OUT,
    TOKEN_TYPE_REDIRECT_APPEND,
    TOKEN_TYPE_HEREDOC,
}   t_token_type;


typedef struct s_token
{
	t_token_type type;
	char *value;
	struct s_token *next;
}	t_token;

// Tokenizer
// It takes a string and spit a list of tokens
// This list will be used to create an Abstract Syntax Tree
t_token *tokenize(char *prompt);
void    free_tokens(t_token *tokens);
void    display_tokens(t_token *tokens);

#endif
