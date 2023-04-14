#ifndef WINDOW_H
# define WINDOW_H

#include <unistd.h>
#include <stdio.h>	// printf
#include <stdlib.h> // malloc, exit
#include <fcntl.h>	// O_RDONLY
#include <errno.h>	// errno
#include <string.h> // strerror
/*#include <keysymdef.h>*/

# define ESC 65307
# define LEFT 97
# define RIGHT 100
# define UP 119
# define DOWN 115

# define FLOOR '0'
# define WALL '1'
# define COLLECTABLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define BAD_ARGS "Bad args m8"
# define BAD_EXTENSION "Bad extension m8"
# define BAD_ELEMENTS "One player, one exit, at least one collectable m8"
# define MALLOC_ERROR "Malloc error m8"
# define MAP_SHAPE "Map's weird wtf"
# define MAP_CHAR "Strange chars in map m8"
# define MAP_LIMITS "Walls are all wrong m8"
typedef struct	s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct	s_window {
	void		*win_ptr;
	t_vector	size;
}				t_window;
typedef struct s_map
{
	int		rows;
	int		cols;
	int		diff;
	int		collectable_count;
	int		exit_count;
	int		player_count;
	int		invalid_char;
	int		invalid_limits;
}	t_map;

typedef struct s_player
{
	int			collectable;
	int			moves;
	t_vector	attempt;
	t_vector	current;
}	t_player;

typedef struct	s_program {
	void		*mlx_ptr;
	int			px;
	t_window	window;
	t_map		map;
	char		**lines;
	void		*floor_img;
	void		*wall_img;
	void		*collectable_img;
	void		*exit_img;
	void		*player_img;
	t_player	player;
}				t_program;

// main.c
void		handle_error(t_program *program, char *message);
int			exit_program(t_program *program);
int			main(int argc, char **argv);

// init.c
void		count_rows_and_cols(char *map_file, t_map *map);
t_window	init_window(t_program program, char *name);
void		init_program(t_program *program);
void		init_lines(char *map_file, t_program *program);
void		init_images(t_program *program);

// render.c
void	render_map(t_program *program);
void 	print_lines(t_program *program);
void 	render_counters(t_program *program);

// validation.c
void validate_arg(int argc, char *argv, t_program *program);
int extension_is_valid(char *map_file_path);
int map_is_valid(char *map_file_path, t_program *program);

// debug.c
void 	print_lines(t_program *program);
void	print_map_validation(t_program *program);

#endif