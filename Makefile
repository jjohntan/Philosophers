NAME = philo


SRCS = philo.c \
	   ft_atol.c \
	   ft_isdigit.c \
	   utils.c \
	   thread.c \
	   routine.c \
	   init.c \
	   monitor.c


OBJS = $(SRCS:.c=.o)

CC = gcc
FSANTIZE = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror #$(FSANTIZE)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
