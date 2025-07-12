NAME = philosopher_bonus

SRCDIR = ./
OBJDIR = obj/

FLAGS = -Wall -Wextra -Werror -g

SRC	=	${SRCDIR}philosopher_bonus.c				\
		${SRCDIR}philosopher_bonus_utils.c			\
		${SRCDIR}philosopher_bonus_table.c			\
		${SRCDIR}philosopher_bonus_simulation.c		\

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