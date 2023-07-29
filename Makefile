# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME			=	philo

# ---- Directories ---- #

DIR_OBJS		=	bin/

DIR_SRCS		=	srcs/

DIR_HEADERS		=	includes/

# ---- Files ---- #

HEADERS_LIST	=	philo.h

SRCS_LIST		=	death_handling.c	fork_utils.c		\
					free_utils.c		global_utils.c		\
					launch_threads.c	main.c				\
					parsing.c			philo_init.c		\
					solo_philo.c		thread_routine.c	\
					time.c

HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra -g3 -fsanitize=thread

FRAMEWORKS		=	-lpthread -D_REENTRANT


# ---- Commands ---- #

RM				=	rm -rf

MKDIR			=	mkdir -p

# ********* RULES ******** #

all				:	${OBJS} ${HEADERS}
					make ${NAME}

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
					${RM} ${OBJS}
					${RM} ${DIR_OBJS}

fclean			:
					make clean
					${RM} ${NAME}

re				:
					make fclean
					make all

.PHONY:	all clean fclean re
