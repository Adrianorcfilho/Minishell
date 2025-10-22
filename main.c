#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	handler_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char	*prompt;
	char	*args[] = {NULL, NULL};
	char	*env[] = {NULL};
	char	buf[10000];
	char	*directory;

	using_history();
	signal(SIGINT, handler_signal);
	while (1)
	{
		prompt = readline("🐚 ➤ ");
		if (!prompt)
			break ;
		add_history(prompt);
		args[0] = prompt;
		if (ft_strcmp(prompt, "pwd") == 0)
		{
			getcwd(buf, 10000);
			printf("%s\n", buf);
		}
		else if (ft_strcmp(prompt, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (execve(args[0], args, env) == -1)
			printf("%s: command not found.\n", prompt);
		free(prompt);
	}
	return (0);
}
