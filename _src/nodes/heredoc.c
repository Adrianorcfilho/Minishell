// minishell
#include <AST.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// remover
#include <string.h>

static char *get_heredoc_content(char *delimiter)
{
    char *line;
    char *content;
    size_t len;
    size_t total_len;
    ssize_t read;
    size_t line_len;

    line = NULL;
    content = NULL;
    len = 0;
    total_len = 0;

    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        read = getline(&line, &len, stdin);

        if (read == -1)
            break;

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (strcmp(line, delimiter) == 0)
            break ;

        // New function
        line_len = strlen(line);
        content = realloc(content, total_len + line_len + 2); // \n e \0
        if (!content)
        {
            free(line);
            return (NULL);
        }

        strcpy(content + total_len, line);
        content[total_len + line_len] = '\n';
        content[total_len + line_len + 1] = '\0';
        total_len += line_len + 1;
    }
    free(line);
    return (content);
}

int exec_heredoc(t_ast_node *node)
{
    return (0);
}

void get_all_heredoc_content(t_ast_node *node)
{
    if (!node)
        return ;
    if (node->type == NODE_HEREDOC)
        node->heredoc_content = get_heredoc_content(node->heredoc_delimiter);
    get_all_heredoc_content(node->left);
    get_all_heredoc_content(node->right);
}
