#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void render_map(t_program *program)
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

				mlx_put_image_to_window(program->mlx_ptr, program->window.win_ptr, program->player_img, j * program->map.px, i * program->map.px);
			}
		}
	}
}

void print_lines(t_program *program)
{
	int i;

	i = 0;
    while (program->lines[i]) {
        printf("%s", program->lines[i++]);
    }
	printf("\n\n");
}

void render_counters(t_program *program)
{
	char	*move_count;
	char	*collectable_count;
	
	move_count = ft_itoa(program->player.moves);
	collectable_count = ft_itoa(program->player.collectable);
	mlx_string_put(program->mlx_ptr, program->window.win_ptr, program->window.size.x - 24, 12, 0x00fffe00, move_count);
	mlx_string_put(program->mlx_ptr, program->window.win_ptr, program->window.size.x - 24, 24, 0x00fffe00, collectable_count);
	free(move_count);
	free(collectable_count);
}