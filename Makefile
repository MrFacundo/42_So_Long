NAME 			= so_long
SOURCES 		= $(shell echo srcs/*.c)
OBJECTS 		= $(SOURCES:.c=.o)
HEADER			= -Iincludes
LIBFT_DIR		= ./libft
MINILIBX_DIR	= ./minilibx-linux
CC 				= gcc
CFLAGS_PROD 	= -g -Wall -Wextra -Werror
LFLAGS		 	= -L$(MINILIBX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

# --- COLORS ---

NONE=\033[0m
GRAY=\033[2;37m
RED=\033[31m
GREEN=\033[32m

# --- RULES ---

all: $(NAME)

$(NAME): $(OBJECTS) minilibx libft
		@echo  "$(GRAY)----Compiling $(NAME)----$(NONE)"
		gcc -o $@ $(OBJECTS) $(LFLAGS)
		@echo "$(GREEN)$(NAME) Compiled! ᕦ(♥_♥)ᕤ$(NONE)\n"

.c.o:	%.o : %.c
		$(CC) $(CFLAGS_PROD) -c $< -o $@

minilibx:
		@echo  "$(GRAY)----Compiling Minilib----$(NONE)"
		make -C $(MINILIBX_DIR)

libft:
		@echo  "$(GRAY)----Compiling Libft----$(NONE)"
		make -C $(LIBFT_DIR)

clean:
		@echo "$(GREEN)Deleting obs! ( ͡° ͜ʖ ͡°) $(NONE)"
		rm -f $(OBJECTS)
		make -C $(MINILIBX_DIR) clean
		make -C $(LIBFT_DIR) clean

fclean:	clean
		@echo "$(RED)Deleting everything! ( ͡° ͜ʖ ͡°) $(NONE)"
		rm -f $(NAME) $(OBJECTS) libft/libft.a

kill:
		kill -9 $$(pidof so_long)

show:
		@printf "NAME	: $(NAME)\n"
		@printf "CC	: $(CC)\n"
		@printf "CFLAGS	: $(CFLAGS_PROD)\n"
		@printf "LFLAGS	: $(LFLAGS)\n"
		@printf "SOURCES	: $(SOURCES)\n"

restart: all
		./so_long maps/map_4.ber

valgrind: all
		 valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./so_long maps/map_4.ber

doadance:
		@echo "\033[33;1m8====D\033[0m"
		@sleep 0.5
		@echo "\033[33;1m8===D~~~  \033[0m"
		@sleep 0.5
		@echo "\033[33;1m8===D  ~~~\033[0m\033[33;1m\o/\o/\033[0m"

re: fclean all

.PHONY: all minilibx libft clean fclean re restart valgrind doadance kill show