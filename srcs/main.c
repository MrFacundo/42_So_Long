/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:28:22 by facundo           #+#    #+#             */
/*   Updated: 2023/04/18 22:01:15 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_program(&game);
	validate_arg(argc, argv[1], &game);
	game.mlx_ptr = mlx_init();
	game.window = init_window(game, "So Long");
	init_images(&game);
	init_game(&game);
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == RESET)
		reset_game(game);
	if (!game->game_over)
	{
		if (keycode == LEFT)
			game->player.attempt.x = game->player.current.x - 1;
		else if (keycode == RIGHT)
			game->player.attempt.x = game->player.current.x + 1;
		else if (keycode == DOWN)
			game->player.attempt.y = game->player.current.y + 1;
		else if (keycode == UP)
			game->player.attempt.y = game->player.current.y - 1;
		else
			return (0);
		if (game->table[game->player.attempt.y][game->player.attempt.x] != WALL)
			move(game);
		else
		{
			game->player.attempt.x = game->player.current.x;
			game->player.attempt.y = game->player.current.y;
		}
	}
	return (0);
}

void	move(t_game *game)
{	
	print_table(game->table);
	if (game->table[game->player.attempt.y][game->player.attempt.x] == COLLECTABLE)
		game->player.collected += 1;
	else if (game->table[game->player.attempt.y][game->player.attempt.x] == EXIT)
	{
		render_game_over_message(game);
		return ;
	}
	game->player.moves += 1;
	game->table[game->player.current.y][game->player.current.x] = FLOOR;
	game->table[game->player.attempt.y][game->player.attempt.x] = PLAYER;
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	render_map(game);
	render_counters(game);
}

void	reset_game(t_game *game)
{
	printf("reset game\n");
	print_table(game->table_copy);
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	free_table(game->table);
	copy_table(game->table_copy, &game->table);
	init_game(game);
}

int	exit_game(t_game *game)
{
	char	**tmp;
	
	printf("closing...");
	if (game->table)
		free_table(game->table);
	if (game->window.win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window.win_ptr);
	exit(0);
}