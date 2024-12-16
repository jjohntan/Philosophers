NAME = philo


SRCS = main.c \
	   ft_atoi.c \
	   ft_isdigit.c \
	   init.c \
	   routine.c \
	   utils.c


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
