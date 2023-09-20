NAME			= philo

SRCS			= philo.c utils.c init.c process.c close.c process_utils.c

OBJS			= ${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

CC				= cc

CFLAGS 			= -Wall -Werror -Wextra

all:			${NAME}

%.o:			%.c Makefile philo.h
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

clean:
				rm -f ${OBJS}

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all bonus clean fclean re
