# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME			=	philo

# ---- Directories ---- #

DIR_OBJS		=	bin/

DIR_SRCS		=	srcs/

DIR_HEADERS		=	includes/

# ---- Files ---- #

HEADERS_LIST	=	philo

SRCS_LIST		=	main.c

HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc

CFLAGS			=	 -Wall -Werror -Wextra -g3

FRAMEWORKS		=	-lpthread -D_REENTRANT


# ---- Commands ---- #

RM				=	rm -rf

MKDIR			=	mkdir -p

# ********* RULES ******** #

all				:	${OBJS} ${HEADERS}
					make ${NAME}

fsanitize		:
					make all CFLAGS+="-fsanitize=address -g3"

no_flags		:
					make fclean
					make all CFLAGS="-g3"

# ---- Variables Rules ---- #

${NAME}			:	${OBJS} ${HEADERS}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} ${FRAMEWORKS} -o ${NAME}

# ---- Compiled Rules ---- #

${OBJS}			:	| ${DIR_OBJS}

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c ${HEADERS}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}

# ---- Usual Rules ---- #

clean			:
					make -C lib/libft clean
					${RM} ${OBJS}
					${RM} ${DIR_OBJS}

fclean			:
					make clean
					${RM} ${NAME}
					make -C lib/libft fclean

re				:
					make fclean
					make all

.PHONY:	all clean fclean re