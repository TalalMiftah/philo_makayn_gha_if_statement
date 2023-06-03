SRC = philo.c \
		start.c \
		utils.c

OBJ = ${SRC:%.c=%.o}

NAME = philo

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
