#include <tokenizer.h>
#include <minilibft.h>
#include <stdio.h>

void display_tokens(t_token *tokens)
{
    char *type_names[7];
    type_names[0] = ft_strdup("WORD");
    type_names[1] = ft_strdup("PIPE");
    type_names[2] = ft_strdup("REDIRECT_IN");
    type_names[3] = ft_strdup("REDIRECT_OUT");
    type_names[4] = ft_strdup("REDIRECT_APPEND");
    type_names[5] = ft_strdup("HEREDOC");

    t_token *token;

    token = tokens;

    printf("Value\t\tType\n");
    printf("--------------\n");
    while(token)
    {
        printf("%s\t\t\t%s\n", token->value, type_names[(int)token->type]);
        token = token->next;
    }
}
