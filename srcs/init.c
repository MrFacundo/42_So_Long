#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

t_window init_window(t_program program, char *name)
{
	t_window window;
	int width;
	int height;
	window.size.x = program.map.cols * program.px;
	window.size.y = program.map.rows * program.px;
	window.win_ptr = mlx_new_window(program.mlx_ptr, window.size.x, window.size.y, name);
	mlx_hook(window.win_ptr, 17, 0, exit_program, &program);
	return (window);
}

void init_program(t_program *program)
{
	program->window.win_ptr = 0;
	program->px = 32;
	program->lines = 0;
	program->map.diff = 0;
	program->map.collectable_count = 0;
	program->map.exit_count = 0;
	program->map.player_count = 0;
	program->map.invalid_char = 0;
	program->map.invalid_limits = 0;
	program->player.collectable = 0;
	program->player.moves = 0;
}

void init_lines(char *map_file, t_program *program)
{
	char **lines;
	int i;
	int fd;

	fd = open(map_file, O_RDONLY);
	lines = ft_calloc(program->map.rows + 1, sizeof(char *));
	if (!lines)
		exit_program(program, "Malloc failed.");
	i = 0;
	while (lines[i++] = ft_get_next_line(fd));
	program->lines = lines;
	print_lines(program);
}

void init_images(t_program *program)
{
	char *line;
	int fd;
	int i;

	program->floor_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/floor.xpm", &program->px, &program->px);
	program->wall_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/wall.xpm", &program->px, &program->px);
	program->collectable_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/collectable.xpm", &program->px, &program->px);
	program->exit_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/exit.xpm", &program->px, &program->px);
	program->player_img = mlx_xpm_file_to_image(program->mlx_ptr, "xpm/player.xpm", &program->px, &program->px);
}