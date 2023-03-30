
INC=%%%%

INCLIB=$(INC)/../lib

CFLAGS= -I$(INC) -O3 -I.. -g

NAME	= so_long
SRC 	= srcs/main.c
OBJ 	= $(SRC:%.c=%.o)
LFLAGS 	= -L ./minilibx-linux/ -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd
CC		= gcc
HEADER			= -Iincludes
RM				= rm -f
CFLAGS_DEV 		= -g
CFLAGS_PROD 	= -Wall -Wextra -Werror -g

all: $(NAME)

# --- COLORS ---
NONE=\033[0m
GRAY=\033[2;37m
RED=\033[31m
GREEN=\033[32m

# --- RULES ---
$(NAME): $(OBJ)
		@echo  "$(GRAY)----Compiling $(NAME)----$(NONE)"
		$(CC) $(HEADER) -o $(NAME) $(OBJ) $(LFLAGS)

show:
		@printf "NAME	: $(NAME)\n"
		@printf "CC	: $(CC)\n"
		@printf "CFLAGS	: $(CFLAGS_DEV)\n"
		@printf "LFLAGS	: $(LFLAGS)\n"
		@printf "SRC	: $(SRC)\n"
		@printf "OBJ	: $(OBJ)\n"


clean:
		@echo "$(GREEN)Deleting obs! ( ͡° ͜ʖ ͡°) $(NONE)\n"
		$(RM) $(OBJ) *~ core *.core

fclean:
		@echo "$(RED)Deleting everything! ( ͡° ͜ʖ ͡°) $(NONE)\n"
		$(RM) $(NAME) $(OBJ) *~ core *.core

re: 	fclean all
