NAME = gnl.a

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f
AR = ar rc
HEADER = gnl.h

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c ${HEADER}
	@${CC} ${CFLAGS} -c ${SRCS}

$(NAME): $(OBJS)
	@${AR} ${NAME} ${OBJS}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re