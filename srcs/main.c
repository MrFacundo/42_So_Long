#include "../minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdio.h> 	// printf
#include <stdlib.h> // malloc, exit
#include <fcntl.h> 	//O_RDONLY

#include "../libft/libft.h"
#include "../includes/window.h"


int     exit_program(t_program program)
{
	printf("closing");
	mlx_destroy_window (program.mlx_ptr, program.window.win_ptr);
	exit(0);
}

t_window	new_window(t_program program , int width, int height, char	*name)
{
	t_window	window;	

	window.win_ptr = mlx_new_window(program.mlx_ptr, width, height, name);
	window.size.x = width;
	window.size.y = height;
	mlx_hook(window.win_ptr, 17, 0, exit_program, &program);
	return (window);
}

/* t_image new_img(void *mlx_ptr, char *path)
{
	t_image image;
	
	printf("mlx_ptr: %p\n",mlx_ptr);
	printf("path: %s\n",path);
	printf("image.size.x: %d\n",image.size.x);
	image.img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &image.size.x, &image.size.y);
	printf("img_ptr: %p\n",image.img_ptr);
	
	image.pixels  = mlx_get_data_addr(image.img_ptr, &image.bits_per_pixel, &image.line_len, &image.endian);
	
	printf("bpp: %d\n",image.bits_per_pixel);
	printf("endian: %d\n",image.endian);
	printf("line_len: %d\n",image.line_len);
	printf("addr: %p\n",image.pixels);
	
	return (image);

} */

/* int	handle_key(int key, void *param)
{
	t_program *program = (t_program *)param;

	mlx_clear_window(program->mlx_ptr, program->window.win_ptr);
	if (key == 'd')
		program->sprite_position.x += program->sprite.size.x;
	else if (key == 'a')
		program->sprite_position.x -= program->sprite.size.x;
	else if (key == 's')
		program->sprite_position.y += program->sprite.size.y;
	else if (key == 'w')
		program->sprite_position.y -= program->sprite.size.y;
	else if (key == 'x')
		mlx_destroy_window(program->mlx_ptr, program->window.win_ptr);
	mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr,
		program->sprite.img_ptr, program->sprite_position.x, program->sprite_position.y);

	printf("Key pressed -> %d\n", key);
	return (0);
}
 */
void	init_lines(char	*map_file, t_program *program)
{
	char	**lines;
	char	*line;
	int		i;
	int		fd;

	fd = open(map_file, O_RDONLY);
	lines = malloc(sizeof(char *) * (program->map.rows + 1));
	i = 0;
	line = ft_get_next_line(fd);
	while(line)
	{
		lines[i++] = line;
		line = ft_get_next_line(fd); // in condition to shorter
	}
	lines[i] = 0;
	program->lines = lines;
	printf("lines amount: %d\n", i);
	printf("first line: %s\n", program->lines[0]);

}

void	init_images(t_program *program)
{
	program->wall = mlx_xpm_file_to_image(program->mlx_ptr, "png/o.png", &program->map.px, &program->map.px);
	program->collectable = mlx_xpm_file_to_image(program->mlx_ptr, "png/c1.png", &program->map.px, &program->map.px);
	program->exit = mlx_xpm_file_to_image(program->mlx_ptr, "png/e.png", &program->map.px, &program->map.px);
	program->player = mlx_xpm_file_to_image(program->mlx_ptr, "png/p1.png", &program->map.px, &program->map.px);
}

void	count_rows_and_cols(char *map_file, t_map *map)
{
	int		i;
	char	*line;
	int		fd;

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

void	print_map(t_program *program)
{
	int		i;
	int		j;

	i = 0;
	while (++i < program->map.rows)
	{
		j = 0;
		while (++j < program->map.cols)
		{
			if (program->lines[i][j] == 'C')
				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->wall, j * program->map.px, i * program->map.px);
		}
	}


}


void	init_program(t_program *program)
{
	program->mlx_ptr = mlx_init();
	program->window = new_window(*program, 500, 500, "myWindow");
	program->map.px = 32;
}

int main(int argc, char **argv)
{
	t_program program;
	
	init_program(&program);
	count_rows_and_cols(argv[1], &program.map);
	init_lines(argv[1], &program);
	init_images(&program);
	// print_map(&program);
	// mlx_key_hook(program.window.win_ptr, *handle_key, &program);
	mlx_loop(program.mlx_ptr);
	return(0);
}