#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/window.h"

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

t_window init_window(t_program program, char *name)
{
	t_window window;
	int width;
	int height;
	printf("program.map.cols %d\n", program.map.cols);
	printf("program.map.rows %d\n", program.map.rows);
	window.size.x = program.map.cols * program.map.px;
	window.size.y = program.map.rows * program.map.px;
	window.win_ptr = mlx_new_window(program.mlx_ptr, window.size.x, window.size.y, name);
	mlx_hook(window.win_ptr, 17, 0, exit_program, &program);
	return (window);
}

void init_program(t_program *program)
{
	program->mlx_ptr = mlx_init();
	program->map.px = 32;
	program->window = init_window(*program, "So Long");
	program->player.collectable = 0;
	program->player.moves = 0;
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