NAME = philo
HEADERS	= -I ./include

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_CFLAGS = -g3
SRCS = src/main.c	src/ft_atoi.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Program Made"

debug: re
	$(CC) $(OBJS) $(HEADERS) $(DEBUG_CFLAGS) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(DEBUG_CFLAGS) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	$(RM) $(OBJS)
	@echo "Cleaned object files"

fclean: clean
	$(RM) $(NAME)
	@echo "Fully Cleaned"

re: fclean all

.PHONY: all clean fclean re debug
