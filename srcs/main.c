#include "../minilibx-linux/mlx.h"
#include <unistd.h>
#include "../includes/window.h"

void *win_ptr;

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int handleKey(int keycode, void *param)
{
	ft_putchar_fd(keycode, 1);
	if (keycode == 'x')
		mlx_destroy_window(mlx_ptr, win_ptr);
	return (0);
}

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





int main()
{
	t_window	my_window;	

	my_window = new_window(500, 500, "myWindow");

	mlx_key_hook(my_window, handleKey, (void *)0);

	mlx_loop(my_window.mlx_ptr);
}