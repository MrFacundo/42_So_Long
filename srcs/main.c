#include "../minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdio.h> // printf
# include <stdlib.h> 	// malloc, exit

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

t_image new_img(void *mlx_ptr, char *path)
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

}

int	handle_key(int key, void *param)
{
	t_program *program = (t_program *)param;

	mlx_clear_window(program->mlx_ptr, program->window.win_ptr);
	if (key == 'd')
		program->sprite_position.x += program->sprite.size.x;
	else if (key == 'a')
		program->sprite_position.x -= program->sprite.size.x;
	else if (key == 'w')
		program->sprite_position.y += program->sprite.size.y;
	else if (key == 's')
		program->sprite_position.y -= program->sprite.size.y;
	else if (key == 'x')
		mlx_destroy_window(program->mlx_ptr, program->window.win_ptr);
	mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr,
		program->sprite.img_ptr, program->sprite_position.x, program->sprite_position.y);

	printf("Key pressed -> %d\n", key);
	return (0);
}

int main()
{
	t_program program;
	
	program.mlx_ptr = mlx_init();
	program.window = new_window(program, 500, 500, "myWindow");
	program.sprite = new_img(program.mlx_ptr, "block.xpm");
	program.sprite_position.x = 0;
	program.sprite_position.y = 0;
	mlx_put_image_to_window(program.mlx_ptr, program.window.win_ptr, program.sprite.img_ptr, program.sprite_position.x, program.sprite_position.y);
	// mlx_key_hook(program.window.win_ptr, *handle_key, &program);
	mlx_loop(program.mlx_ptr);
	return(0);
}