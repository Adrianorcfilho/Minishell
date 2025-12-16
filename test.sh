make re && valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --suppressions=ignore_readline.supp -s ./minishell
