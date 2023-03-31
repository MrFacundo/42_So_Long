#include "../minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdio.h> // printf
# include <stdlib.h> 	// malloc, exit

#include "../includes/window.h"

// void *win_ptr;

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

/* 
int handleKey(int keycode, void *param)
{
	ft_putchar_fd(keycode, 1);
	if (keycode == 'x')
		mlx_destroy_window(my_window.mlx_ptr, my_window.win_ptr);
	return (0);
} */

t_window	new_window(int width, int height, char	*name)
{
	void		*mlx_ptr;
	t_window	new_window;	
	
	mlx_ptr = mlx_init();
	new_window.mlx_ptr = mlx_ptr;
	new_window.win_ptr = mlx_new_window(mlx_ptr, width, height, name);
	new_window.width = width;
	new_window.height = height;

	return (new_window);
}

t_img	new_img(t_window my_window, int height, int width)
{
	t_img	new_image;
	
	new_image.win = my_window;
	new_image.img_ptr = mlx_new_image(my_window.mlx_ptr, width, height);
	new_image.addr = mlx_get_data_addr(new_image.img_ptr, &(new_image.bpp), &(new_image.line_len), &(new_image.endian));
	new_image.height = 4;
	new_image.width = 4;
	
	printf("img_ptr: %p\n",new_image.img_ptr);
	printf("bpp: %d\n",new_image.bpp);
	printf("endian: %d\n",new_image.endian);
	printf("line_len: %d\n",new_image.line_len);
	printf("addr: %p\n",new_image.addr);

	return (new_image);
}

int     exit_tutorial(t_window *window)
{
	if (window)
		mlx_destroy_window (window->mlx_ptr, window->win_ptr);
	exit(0);
}

int main()
{
	t_window	my_window;	
	t_img	my_image;

	my_window = new_window(500, 500, "myWindow");
	// mlx_key_hook(my_window.win_ptr, handleKey, (void *)0);
	my_image = new_img(my_window, 4, 4);
	ft_memcpy(my_image.addr, "s4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vfs4vf", 16*4);
	mlx_put_image_to_window(my_image.win.mlx_ptr, my_image.win.win_ptr, my_image.img_ptr, 10, 10);
	mlx_hook(my_window.win_ptr, 17, 0, exit_tutorial, &my_window);
	mlx_loop(my_window.mlx_ptr);
	return(0);
}