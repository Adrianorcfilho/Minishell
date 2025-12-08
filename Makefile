NAME 	:= minishell
CFLAGS	:= -g
INCS	:= -I_inc/
LIBS	:= -lreadline

SRC		:= main.c
SRC 	+= _src/minilibft/ft_strchr.c
SRC 	+= _src/minilibft/ft_strlen.c
SRC 	+= _src/minilibft/ft_strdup.c
SRC 	+= _src/minilibft/ft_strndup.c
SRC		+= _src/minilibft/ft_isalnum.c
SRC		+= _src/minilibft/ft_itoa.c
SRC 	+= _src/minilibft/ft_memcpy.c
SRC 	+= _src/minilibft/ft_strcmp.c
SRC 	+= _src/minilibft/ft_strcpy.c
SRC 	+= _src/minilibft/ft_realloc.c
SRC 	+= _src/minilibft/ft_putendl_fd.c
SRC 	+= _src/minilibft/ft_substr.c
SRC 	+= _src/minilibft/ft_atoi.c
SRC 	+= _src/minilibft/ft_isdigit.c
SRC 	+= _src/minilibft/ft_isalpha.c
SRC 	+= _src/minilibft/ft_split.c
SRC 	+= _src/minilibft/ft_strjoin.c
SRC 	+= _src/AST/AST_0.c
SRC 	+= _src/AST/AST_1.c
SRC 	+= _src/AST/AST_debug.c
SRC 	+= _src/AST/check_syntax.c
SRC 	+= _src/tokenizer/tokenizer_0.c
SRC 	+= _src/tokenizer/tokenizer_1.c
SRC 	+= _src/tokenizer/tokenizer_debug.c
SRC		+= _src/execution/safe_fork.c
SRC		+= _src/execution/is_builtin.c
SRC 	+= _src/execution/exit_status.c
SRC		+= _src/execution/execution_0.c
SRC		+= _src/execution/execution_1.c
SRC		+= _src/execution/execution_2.c
SRC		+= _src/execution/execution_3.c
SRC		+= _src/execution/execution_4.c
SRC		+= _src/execution/find_path.c
SRC		+= _src/execution/pipe_0.c
SRC		+= _src/execution/pipe_1.c
SRC		+= _src/execution/heredoc_0.c
SRC		+= _src/execution/heredoc_1.c
SRC		+= _src/built_in/cd.c
SRC		+= _src/built_in/env.c
SRC		+= _src/built_in/export.c
SRC		+= _src/built_in/pwd.c
SRC		+= _src/built_in/unset.c
SRC		+= _src/built_in/exit.c
SRC		+= _src/built_in/echo.c
SRC 	+= _src/map/map_0.c
SRC 	+= _src/map/map_1.c
SRC 	+= _src/map/map_2.c
SRC 	+= _src/map/free_map.c
SRC 	+= _src/expander/expander_0.c
SRC 	+= _src/expander/expander_1.c
SRC 	+= _src/expander/expander_2.c
SRC 	+= _src/signals/signals.c

$(NAME): $(SRC)
	@cc $(CFLAGS) $(INCS) $(SRC) -o $(NAME) $(LIBS)
	@for f in $(SRC); do echo "Compilling $$f..."; done
	@echo "$(NAME) created."

all: $(NAME)

clean:
	rm -f _src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
