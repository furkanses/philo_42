NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c init.c philosopher.c monitor.c utils.c cleanup.c actions.c take_fork1.c take_fork2.c eat_meal.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -fsanitize=thread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 