#SETUP
NAME		=	philo
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
SRCS		=	philo.c utils.c inits.c observer.c routine.c
OBJ			=	$(SRCS:.c=.o)

HEADERS		=	philo.h

#COMMANDS
%.o: %.c $(HEADERS) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ)
				@$(CC) $(OBJ) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJ)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
