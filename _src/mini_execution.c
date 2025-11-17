#include <stdio.h>
#include <unistd.h>
#include <mini_execution.h>
#include <AST.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <error_log.h>
#include <permitions.h>

int exec_command(t_ast_node *node)
{
    pid_t pid;

    if (!node || node->type != NODE_COMMAND)
        return (-1);
    if (node->arg_count == 0)
        return (0);
    // if not built-in
    pid = fork();
    if (pid == 0)
        execvp(node->args[0], node->args);
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    // if built in
    return (0);
}

int exec_pipe(t_ast_node *node)
{
    int fd[2];
    pid_t left_pid;
    pid_t right_pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return -1;
    }
    left_pid = fork();
    if (left_pid == -1)
    {
        perror("fork");
        return -1;
    }
    if (left_pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        exec_node(node->left);
        exit(0);
    }
    right_pid = fork();
    if (right_pid == -1)
    {
        perror("fork");
        return -1;
    }
    if (right_pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        exec_node(node->right);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
    return (0);
}


int exec_redirect_in(t_ast_node *node)
{
    int fd;
    pid_t pid;

    if (!node->filename)
    {
        fprintf(stderr, "Missing file name for redirection\n");
        return -1;
    }

    if (!node->left || node->left->type != NODE_COMMAND)
    {
        fprintf(stderr, "Invalid redirect structure\n");
        return -1;
    }

    fd = open(node->filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    pid = fork();
    if (pid == 0)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(fd);
            exit(1);
        }
        close(fd);
        exec_node(node->left);
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
    else
    {
        perror("fork");
        close(fd);
        return -1;
    }

    return 0;
}

int safe_open(enum e_node_type type, char *filename)
{
    int fd;

    if (type == NODE_REDIRECT_IN)
        fd = open(filename, O_RDONLY);
    else if (type == NODE_REDIRECT_OUT)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, USER_RW_OTHERS_R);
    else if (type == NODE_REDIRECT_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, USER_RW_OTHERS_R);
    if (fd == -1)
    {
        perror("open");
    }
    return (fd);
}

int exec_redirect(t_ast_node *node)
{
    int fd;
    pid_t pid;

    if (!node->filename)
    {
        fprintf(stderr, MISSING_FILE_FOR_DIRECTION);
        return (-1);
    }

    if (!node->left || node->left->type != NODE_COMMAND)
    {
        fprintf(stderr, INVALID_STRUCTURE_FOR_DIRECTION);
        return (-1);
    }

    // create safe_open
    fd = safe_open(node->type, node->filename);
    pid = fork();
    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exec_node(node->left);
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
    return (0);
}

int exec_node(t_ast_node *node)
{
    if (!node)
        return (-1);
    if (node->type == NODE_COMMAND)
        return exec_command(node);
    else if (node->type == NODE_PIPE)
        return exec_pipe(node);
    else if (node->type == NODE_REDIRECT_IN)
        return exec_redirect_in(node);
    else if (node->type == NODE_REDIRECT_OUT || node->type == NODE_REDIRECT_APPEND)
        return exec_redirect(node);
    else if(node->type == NODE_HEREDOC)
        return exec_heredoc(node);
    else
    {
        printf("Volte outro dia....");
        return (-1);
    }
}

int exec_ast(t_ast_node *node)
{
    get_all_heredoc_content(node);
    return (exec_node(node));
}
