/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:28:22 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 19:16:52 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

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

void	init_game(t_game *game)
{
	game->map.player_count = 0;
	game->player.collected = 0;
	game->player.moves = 0;
	game->game_over = 0;
	render_map(game);
	mlx_key_hook(game->window.win_ptr, handle_key, game);
	mlx_loop(game->mlx_ptr);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == 'r')
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
