#include "../minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdio.h>	// printf
#include <stdlib.h> // malloc, exit
#include <fcntl.h>	//O_RDONLY

#include "../libft/libft.h"
#include "../includes/window.h"

int exit_program(t_program *program)
{
	printf("closing");
	mlx_destroy_window(program->mlx_ptr, program->window.win_ptr);
	exit(0);
}

t_window new_window(t_program program, int width, int height, char *name)
{
	t_window window;

	window.win_ptr = mlx_new_window(program.mlx_ptr, width, height, name);
	window.size.x = width;
	window.size.y = height;
	mlx_hook(window.win_ptr, 17, 0, exit_program, &program);
	return (window);
}

void print_map(t_program *program)
{
	int i;
	int j;

	i = -1;
	while (++i < program->map.rows)
	{
		j = -1;
		while (++j < program->map.cols)
		{
			if (program->lines[i][j] == WALL)
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->wall_img, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == FLOOR)
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->floor_img, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == COLLECTABLE)
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->collectable_img, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == EXIT)
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->exit_img, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == PLAYER)
			{
				program->player.current.x = j;
				program->player.current.y = i;
				program->player.attempt.x = j;
				program->player.attempt.y = i;
				printf("program->player.current.y -> %d, program->player.current.x-> %d\n", program->player.current.y, program->player.current.x);

				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->player_img, j * program->map.px, i * program->map.px);
			}
		}
	}
}

void print_lines(t_program *program)
{
	int i;

	i = 0;
	while (program->lines[i])
	{
		printf("%s", program->lines[i]);
		i++;
	}
}

void	move(t_program *program)
{
	printf("program->lines[program->player.current.y][program->player.current.x]-> %c\n", program->lines[program->player.current.y][program->player.current.x]);
	print_lines(program);
	program->lines[program->player.current.y][program->player.current.x] = FLOOR;
	program->lines[program->player.attempt.y][program->player.attempt.x] = PLAYER;
	print_lines(program);

	mlx_clear_window(program->mlx_ptr, &program->window);
	print_map(program);
}

int	handle_key(int keycode, t_program *program)
{
	if (keycode == ESC)
		exit_program(program);
	else if (keycode == LEFT)
		program->player.attempt.x = program->player.current.x - 1;
	else if (keycode == RIGHT)
	{
		printf("program->player.current.x  -> %d\n", program->player.current.x);
		printf("program->player.current.y  -> %d\n", program->player.current.y);
		printf("program->player.attempt.x  -> %d\n", program->player.attempt.x);
		printf("program->player.attempt.y  -> %d\n", program->player.attempt.y);

		program->player.attempt.x = program->player.current.x + 1;
	}
	else if (keycode == DOWN)
		program->player.attempt.y = program->player.current.y + 1;
	else if (keycode == UP)
		program->player.attempt.y = program->player.current.y - 1;
	else
		return (0);
	if (program->lines[program->player.attempt.y][program->player.attempt.x] != WALL)
		move(program);
	else
	{
		program->player.attempt.x = program->player.current.x;
		program->player.attempt.y = program->player.current.y;
	}
	return (0);
}

void init_lines(char *map_file, t_program *program)
{
	char **lines;
	char *line;
	int i;
	int fd;

	fd = open(map_file, O_RDONLY);
	lines = malloc(sizeof(char *) * (program->map.rows + 1));
	i = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		lines[i++] = line;
		line = ft_get_next_line(fd); // in condition to shorter
	}
	lines[i] = 0;
	program->lines = lines;
}

void init_images(t_program *program)
{
	char *line;
	int fd;
	int i;

	program->floor_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/floor.xpm", &program->map.px, &program->map.px);
	program->wall_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/wall.xpm", &program->map.px, &program->map.px);
	program->collectable_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/collectable.xpm", &program->map.px, &program->map.px);
	program->exit_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/exit.xpm", &program->map.px, &program->map.px);
	program->player_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/player.xpm", &program->map.px, &program->map.px);

}

void count_rows_and_cols(char *map_file, t_map *map)
{
	int i;
	char *line;
	int fd;

	i = 1;
	fd = open(map_file, O_RDONLY);
	while (ft_get_next_line(fd))
	{
		if (i == 1)
			map->cols = ft_strlen(ft_get_next_line(fd));
		i++;
	}
	map->rows = i;
}

void init_program(t_program *program)
{
	program->mlx_ptr = mlx_init();
	program->window = new_window(*program, 500, 500, "myWindow");
	// program->map.px = 32;
}

int main(int argc, char **argv)
{
	t_program program;

	init_program(&program);
	count_rows_and_cols(argv[1], &program.map);
	init_lines(argv[1], &program);
	init_images(&program);
	print_map(&program);
	mlx_key_hook(program.window.win_ptr, handle_key, &program);
	mlx_loop(program.mlx_ptr);
	return (0);
}