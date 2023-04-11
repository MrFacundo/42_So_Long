#ifndef WINDOW_H
# define WINDOW_H

#include <unistd.h>
#include <stdio.h>	// printf
#include <stdlib.h> // malloc, exit
#include <fcntl.h>	// O_RDONLY

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
typedef struct	s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct	s_window {
	void		*win_ptr;
	t_vector	size;
}				t_window;

typedef struct	s_image {
	void		*img_ptr;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		px;
	int		a;
	int		b;
	char	**lines;
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
int			exit_program(t_program *program);
void		print_map(t_program *program);
int			main(int argc, char **argv);

// init.c
void		count_rows_and_cols(char *map_file, t_map *map);
t_window	init_window(t_program program, char *name);
void		init_program(t_program *program);
void		init_lines(char *map_file, t_program *program);
void		init_images(t_program *program);

#endif