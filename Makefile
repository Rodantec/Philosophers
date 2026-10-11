NAME = philo

SOURCES = main.c \
			parsing.c \
			init.c \
			routine.c \
			utils.c \
			utils1.c \
			monitor.c \

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

$(NAME) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

all: $(NAME)

clean:
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
