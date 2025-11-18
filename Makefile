NAME 	:= minishell
CFLAGS	:= -g -lreadline
INCS	:= -I_inc/
LIBS	:=

SRC		:= main.c
SRC 	+= _src/minilibft/ft_strchr.c
SRC 	+= _src/minilibft/ft_strlen.c
SRC 	+= _src/minilibft/ft_strdup.c
SRC 	+= _src/minilibft/ft_strndup.c
SRC 	+= _src/tokenizer.c
SRC 	+= _src/AST.c
SRC 	+= _src/tokenizer_debug.c
SRC 	+= _src/AST_debug.c
SRC		+= _src/mini_execution.c
SRC		+= _src/nodes/heredoc.c


all: $(NAME)

$(NAME): $(SRC)
	cc $(CFLAGS) $(INCS) $(SRC) -o $(NAME) $(LIBS)

clean:
	rm -f _src/*.o

fclean: clean
	@rm -f $(NAME)
