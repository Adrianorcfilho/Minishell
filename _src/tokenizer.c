#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <tokenizer.h>
#include <minilibft.h>

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);

    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;
    return (token);
}

void link_tokens(t_token **tokens, t_token *new)
{
    t_token *last;

    if (*tokens == NULL)
        *tokens = new;
    else
    {
        last = *tokens;
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

int handle_special(char *input, int index, t_token **tokens)
{
    if (input[index] == '|')
    {
        link_tokens(tokens, create_token(TOKEN_TYPE_PIPE, "|"));
    	return (1);
    }
    else if (input[index] == '<')
    {
        if (input[index + 1] == '<')
        {
            link_tokens(tokens, create_token(TOKEN_TYPE_HEREDOC, "<<"));
            return (2);
        }
        link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_IN, "<"));
        return (1);
    }
    else if (input[index] == '>')
    {
        if (input[index + 1] == '>')
        {
            link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_APPEND, ">>"));
            return (2);
        }
        link_tokens(tokens, create_token(TOKEN_TYPE_REDIRECT_OUT, ">"));
        return (1);
    }
    return (0);
}

int handle_word(char *input, t_token **tokens)
{
    int i;
    char *word;

    i = 0;
    while (input[i])
    {
        if (ft_strchr(" |><", input[i]))
            break;
        i++;
    }
    word = ft_strndup(input, i);
    if (word)
    {
        link_tokens(tokens, create_token(TOKEN_TYPE_WORD, word));
        free(word);
    }
    return (i);
}

t_token *tokenize(char *prompt)
{
    t_token *tokens;
    int i;

    tokens = NULL;
    i = 0;
    while (prompt[i])
    {
        while (prompt[i] && ft_strchr(" ", prompt[i]))
            i++;

        if (ft_strchr("|><", prompt[i]))
            i += handle_special(prompt, i, &tokens);
        else
            i += handle_word(&prompt[i], &tokens);
    }
    return (tokens);
}

void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}



/*
int main(int argc, char **argv)
{

    t_token *tokens;

    tokens = tokenize(argv[1]);
    display_tokens(tokens);
    return (0);
}
*/
