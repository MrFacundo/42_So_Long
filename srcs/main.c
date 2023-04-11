#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/window.h"

int exit_program(t_program *program)
{
	printf("closing");
	mlx_destroy_window(program->mlx_ptr, program->window.win_ptr);
	exit(0);
}

void	move(t_program *program)
{	
	print_lines(program);
	if (program->lines[program->player.attempt.y][program->player.attempt.x] == COLLECTABLE)
		program->player.collectable += 1;
	else if (program->lines[program->player.attempt.y][program->player.attempt.x] == EXIT)
		exit_program(program);
	program->player.moves += 1;
	program->lines[program->player.current.y][program->player.current.x] = FLOOR;
	program->lines[program->player.attempt.y][program->player.attempt.x] = PLAYER;
	mlx_clear_window(program->mlx_ptr, program->window.win_ptr);
	render_map(program);
	render_counters(program);
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


int main(int argc, char **argv)
{
	t_program program;

	count_rows_and_cols(argv[1], &program.map);
	init_program(&program);
	init_lines(argv[1], &program);
	init_images(&program);
	render_map(&program);
	mlx_key_hook(program.window.win_ptr, handle_key, &program);
	mlx_loop(program.mlx_ptr);
	return (0);
}