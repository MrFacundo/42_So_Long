#include "../minilibx-linux/mlx.h"

int main()
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 500, 500, "myWindow");
	mlx_loop(mlx_ptr);

}