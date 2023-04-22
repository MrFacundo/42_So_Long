/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:21:31 by facundo           #+#    #+#             */
/*   Updated: 2023/04/22 16:10:19 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h> // read, close
# include <stdio.h>	// printf
# include <stdlib.h> // malloc, exit
# include <fcntl.h>	// O_RDONLY
# include <errno.h>	// errno
# include <string.h> // strerror

// key codes
# define ESC 65307
# define LEFT 97
# define RIGHT 100
# define UP 119
# define DOWN 115
# define RESET 102

// map elements
# define FLOOR '0'
# define WALL '1'
# define COLL 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'V'

// error messages
# define BAD_ARGS "Bad args m8"
# define BAD_EXTENSION "Bad extension m8"
# define BAD_ELEMENTS "One player, one exit, at least one collectable m8"
# define MALLOC_ERROR "Malloc error m8"
# define MAP_SHAPE "Map's all weird wtf"
# define MAP_ROWS "Min 3 rows m8"
# define MAP_CHAR "Strange chars in map m8"
# define MAP_LIMITS "Map borders are all wrong m8"
# define BAD_PATH "No valid path to exit m8"
# define IMG_ERROR "Image loading issues"

// game messages
# define WIN_MSG "You win!"
# define LOSE_MSG "Game Over"
# define RESET_MSG_1 "Press F to restart"
# define RESET_MSG_2 "Press F to pay respects"

// colors
# define YELLOW 0x008fce00

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
typedef struct s_map
{
	int	rows;
	int	cols;
	int	diff;
	int	exit_count;
	int	player_count;
	int	enemy_count;
	int	collectable_count;
	int	invalid_char;
	int	invalid_limits;
}	t_map;

typedef struct s_player
{
	int			collected;
	int			moves;
	t_vector	attempt;
	t_vector	current;
}	t_player;

typedef struct s_enemy
{
	t_vector	current;
}	t_enemy;

typedef struct s_img_ptrs
{
	void	*wall;
	void	*coll;
	void	*exit;
	void	*player;
	void	*player1;
	void	*player2;
	void	*player3;
	void	*player_end;
	void	*enemy;
	void	*enemy1;
	void	*enemy2;
}	t_img_ptrs;

typedef struct s_game
{
	void		*mlx_ptr;
	int			px;
	t_window	window;
	t_map		map;
	t_img_ptrs	images;
	int			image_load_success;
	char		**table;
	char		**table_copy;
	char		**table_copy2;
	t_player	player;
	t_enemy		*enemies;
	int			game_over;
}	t_game;

//functions

// init.c
void		init_game(t_game *game);
t_window	init_window(t_game program, char *name);
void		init_program(t_game *program);
void		init_table(char *map_file, t_game *program);
void		init_images(t_game *program);

// main.c
int			main(int argc, char **argv);
int			handle_key(int keycode, t_game *game);
void		move(t_game *game);
void		reset_game(t_game *game);
int			exit_game(t_game *program);

// map_checks.c
void		set_map_rows(char *map_file_path, t_game *game);
void		check_characters(char *row, int row_number, t_game *program);
void		check_length(char *row, int row_number, t_game *program);
void		check_limits(char *row, int row_number, t_game *program);
void		check_row(char *row, int row_number, t_game *program);

// render.c
void		render_map(t_game *program);
void		render_counters(t_game *program);
void		render_game_over_message(t_game *g, int condition);
void		animate(t_game *game);

// utils.c
void		free_table(char ***tab);
void		handle_error(t_game *program, char *message);
int			get_fd(char *map_file_path, t_game *program);
void		reset_player_position(t_game *game, int y, int x);
void		copy_table(char **src, char ***dst);

// validation.c
void		validate_arg(int argc, char *argv, t_game *program);
int			extension_is_valid(char *map_file_path);
int			map_is_valid(char *map_file_path, t_game *program);
int			paths_are_valid(t_game *game);
int			flood_fill(char **table, int y, int x, int *requirements);

// debug.c
void		print_table(char **table_ptr);
void		print_map_validation(t_game *program);

// enemy.c
void	init_enemies(t_game *game);
int		reset_enemy_position(t_game *g, int i, int j, int k);
void	move_enemies(t_game *g);


#endif