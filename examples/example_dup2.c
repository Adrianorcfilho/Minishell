#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int pipe_fd[2];

    pipe(pipe_fd);
    // Fiote
    if (fork() == 0)
    {
        close(pipe_fd[1]);                  // Fiote nao escreve
        dup2(pipe_fd[0], STDIN_FILENO);     // STDIN le do pipe!
        execlp("wc", "wc", NULL);           // executa wc, a entrada vem do pipe
    }
    else
    {
        close(pipe_fd[0]);                  // Paiote nao faz leitura
        write(pipe_fd[1], "Banana", 6);     // Escreve no pipe
    }
}

/*  o dup2 permite redirectionar os fds. Na pratica, faz com que
 * o STDIN ou STDOUT leia/escreva em outro fd.
 */
