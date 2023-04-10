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

int	handle_key(int keycode, t_program *program)
{

	if (keycode == ESC)
		exit_program(program);
	else if (keycode == LEFT)
		program->player.attempt.x = program->player.current.x - 1;
	else if (keycode == RIGHT)
		program->player.attempt.x = program->player.current.x + 1;
	else if (keycode == DOWN)
		program->player.attempt.y = program->player.current.y + 1;
	else if (keycode == UP)
		program->player.attempt.y = program->player.current.y - 1;
	if (program->lines[program->player.attempt.y][program->player.attempt.x] != '1')
		move(program);
	else
	{
		program->player.attempt.x = program->player.current.x;
		program->player.attempt.y = program->player.current.y;
	}
	printf("Keycode pressed -> %d\n", keycode);
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
	printf("lines amount: %d\n", i);
	printf("first line: %s\n", program->lines[0]);
}

void init_images(t_program *program)
{
	char *line;
	int fd;
	int i;

	program->floor = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/floor.xpm", &program->map.px, &program->map.px);
	program->wall = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/wall.xpm", &program->map.px, &program->map.px);
	program->collectable = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/collectable.xpm", &program->map.px, &program->map.px);
	program->exit = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/exit.xpm", &program->map.px, &program->map.px);
	program->player = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/player.xpm", &program->map.px, &program->map.px);

	printf("program->map.px %d\n", program->map.px);
	printf("program->floor %p\n", program->floor);
	printf("program->wall %p\n", program->wall);
	printf("program->collectable %p\n", program->collectable);
	printf("program->exit %p\n", program->exit);
	printf("program->player %p\n", program->player);
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
	printf("rows: %d\n", map->rows);
	printf("cols: %d\n", map->cols);
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
			if (program->lines[i][j] == '1')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->wall, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == '0')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->floor, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == 'C')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->collectable, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == 'E')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->exit, j * program->map.px, i * program->map.px);
			else if (program->lines[i][j] == 'P')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->player, j * program->map.px, i * program->map.px);		}
	}
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