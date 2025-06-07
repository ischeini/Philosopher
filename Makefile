NAME = philosopher

SRCDIR = ./
OBJDIR = obj/

FLAGS = -Wall -Wextra -Werror -g

SRC	=	${SRCDIR}philosopher.c					\
		${SRCDIR}philosopher_init.c				\
		${SRCDIR}philosopher_utils.c			\
		${SRCDIR}philosopher_table.c			\
		${SRCDIR}philosopher_error.c			\
		${SRCDIR}philosopher_simulation.c		\
		${SRCDIR}philosopher_simulation_utils.c	\

OBJ = ${SRC:${SRCDIR}%.c=${OBJDIR}%.o}

all:${NAME}

${NAME}: ${OBJ}
	@cc ${FLAGS} -o ${NAME} ${OBJ}

${OBJDIR}:
	@mkdir -p $@

${OBJDIR}%.o: ${SRCDIR}%.c | ${OBJDIR}
	@gcc ${FLAGS} -c $< -o $@

clean:
	@rm -rf ${OBJDIR}

fclean: clean
	@rm -rf ${NAME}


re: fclean all


.PHONY: all clean fclean re