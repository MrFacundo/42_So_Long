NAME 			= so_long
SOURCES 		=  ./srcs/main.c ./srcs/init.c ./srcs/render.c
OBJECTS 		= $(SOURCES:.c=.o)
HEADER			= -Iincludes
LIBFT_DIR		= ./libft
MINILIBX_DIR	= ./minilibx-linux
CC 				= gcc
CFLAGS_PROD 	= -g
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

fclean:
		@echo "$(RED)Deleting everything! ( ͡° ͜ʖ ͡°) $(NONE)"
		rm -f $(NAME) $(OBJECTS) libft/libft.a
		
show:
		@printf "NAME	: $(NAME)\n"
		@printf "CC	: $(CC)\n"
		@printf "CFLAGS	: $(CFLAGS_DEV)\n"
		@printf "LFLAGS	: $(LFLAGS)\n"
		@printf "SRC	: $(SRC)\n"
		@printf "OBJ	: $(OBJ)\n"

restart: all
		./so_long maps/map_1.ber

re: fclean all

.PHONY: all bonus minilibx libft clean fclean re