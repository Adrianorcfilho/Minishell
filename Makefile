NAME 	:= minishell
SRC	:= main.c
CFLAGS	:= 	
LIBS	:= -lreadline	

all: $(NAME)

$(NAME): $(SRC)
	cc $(SRC) -o $(NAME) $(LIBS)
