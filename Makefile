NAME = pipex

SRC = pipex.c pipex_dop.c

OBJ = $(SRC:.c=.o)

HDRS = pipex.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME): $(HDRS) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean
