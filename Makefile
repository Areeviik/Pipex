SRCS = pipex.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

CC = gcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS}  -o ${NAME} $(OBJS) -Llibft -lft

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
