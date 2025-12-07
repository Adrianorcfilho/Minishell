#include <AST.h>
#include <execution.h>
#include <expander.h>
#include <map.h>
#include <minilibft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <signals.h>
#include <stdlib.h>
#include <tokenizer.h>

int	main(int argc, char **argv, char **env)
{
	t_map_str_str	*map_env;

	map_env = env_init(env);
	char **arr = map_as_c_array(map_env);
	ft_free(arr);
	free_map(map_env);
	return (0);
}
