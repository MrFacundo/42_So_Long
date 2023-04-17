/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facundo <facundo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:21:31 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 17:54:01 by facundo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>	// printf
# include <stdlib.h> // malloc, exit
# include <fcntl.h>	// O_RDONLY
# include <errno.h>	// errno
# include <string.h> // strerror
/*# include <keysymdef.h>*/

// key codes
# define ESC 65307
# define LEFT 97
# define RIGHT 100
# define UP 119
# define DOWN 115

// map elements
# define FLOOR '0'
# define WALL '1'
# define COLLECTABLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

// error messages
# define BAD_ARGS "Bad args m8"
# define BAD_EXTENSION "Bad extension m8"
# define BAD_ELEMENTS "One player, one exit, at least one collectable m8"
# define MALLOC_ERROR "Malloc error m8"
# define MAP_SHAPE "Map's all weird wtf"
# define MAP_ROWS "Min 3 rows m8"
# define MAP_CHAR "Strange chars in map m8"
# define MAP_LIMITS "Walls are all wrong m8"
# define BAD_PATH "No valid path to exit m8"

// structs
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_window
{
	void		*win_ptr;
	t_vector	size;
}	t_window;

typedef struct s_img
{
	t_window	window;
	void		*img_ptr;
	char		*addr;
	int			height;
	int			width;
	int			bpp;
	int			endian;
	int			line_len;
}		t_img;

typedef struct s_map
{
	int	rows;
	int	cols;
	int	diff;
	int	exit_count;
	int	player_count;
	int	collectable_count;
	int	invalid_char;
	int	invalid_limits;
}	t_map;

typedef struct s_player
{
	int			collectable;
	int			moves;
	t_vector	attempt;
	t_vector	current;
}	t_player;

typedef struct s_img_ptrs
{
	void	*floor;
	void	*wall;
	void	*coll;
	void	*exit;
	void	*player;
}	t_img_ptrs;

typedef struct s_game
{
	void		*mlx_ptr;
	int			px;
	t_window	window;
	t_map		map;
	t_img_ptrs	images;
	char		**table;
	char		**table_copy;
	t_player	player;
	int			game_over;
}	t_game;

//functions
// main.c
void		handle_error(t_game *program, char *message);
int			main(int argc, char **argv);

// init.c
void		count_rows_and_cols(char *map_file, t_map *map);
t_window	init_window(t_game program, char *name);
void		init_game(t_game *program);
void		init_images(t_game *program);

// render.c
void		render_map(t_game *program);
void		render_counters(t_game *program);

// validation.c
void		validate_arg(int argc, char *argv, t_game *program);
int			extension_is_valid(char *map_file_path);
int			map_is_valid(char *map_file_path, t_game *program);
void		init_table(char *map_file, t_game *program, char ***table_ptr);

// debug.c
void		print_table(char **table_ptr);
void		print_map_validation(t_game *program);

// utils.c
void		free_table(char **tab);
int			exit_game(t_game *program);
void		handle_error(t_game *program, char *message);
int			open_and_check(int fd, char *map_file_path, t_game *program);
void		reset_player_location(t_game *game, int y, int x);

// map_checks.c
void		check_characters(char *row, int row_number, t_game *program);
void		check_length(char *row, int row_number, t_game *program);
void		check_limits(char *row, int row_number, t_game *program);
void		check_row(char *row, int row_number, t_game *program);

// game_over.c
void		render_background(t_game *game);
void		render_game_over_message(t_game *g);


#endif