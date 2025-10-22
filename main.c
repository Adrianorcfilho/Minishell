#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while ((s1[i] || s2[i]) && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}





int main()
{
	char *prompt;
	char *args[] = { NULL, NULL }; 	
   	char *env[] = { NULL };
	
	using_history();
	
	
	while (1)
	{
	
		prompt = readline("🐚 ➤ ");
		
		if (!prompt)
			break;
			
		add_history(prompt);	
		
		args[0] = prompt;
	
		if(ft_strcmp(prompt, "pwd") == 0)
		{
			char buf[10000];

			getcwd(buf, 10000);
			printf("%s\n", buf);
		}
		else if(ft_strcmp(prompt, "cd") == 0)
		{
			
		}
		else if(execve(args[0], args, env ) == -1)
			printf("%s: command not found.\n", prompt);
			
		free(prompt);
	}

	return 0;
}
