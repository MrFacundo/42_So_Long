/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:28:22 by facundo           #+#    #+#             */
/*   Updated: 2023/04/20 20:13:04 by ftroiter         ###   ########.fr       */
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
	game.window = init_window(game, "so long");
	init_images(&game);
	init_game(&game);
	return (0);
}

/* Input management. Called each time a key is pressed. */
int	handle_key(int keycode, t_game *game)
{
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

/* Move the player to the next position. */
void	move(t_game *g)
{	
	printf("move table %p\n", g->table);
	print_table(g->table);
	if (g->table[g->player.attempt.y][g->player.attempt.x] == COLL)
		g->player.collected += 1;
	else if (g->table[g->player.attempt.y][g->player.attempt.x] == EXIT)
	{
		render_game_over_message(g);
		return ;
	}
	g->player.moves += 1;
	animate(g);
	g->table[g->player.current.y][g->player.current.x] = FLOOR;
	g->table[g->player.attempt.y][g->player.attempt.x] = PLAYER;
	mlx_clear_window(g->mlx_ptr, g->window.win_ptr);
	render_map(g);
	render_counters(g);
}

/* Clears the window, resets the table and re-initializes the game. */
void	reset_game(t_game *game)
{
	printf("reset game\n");
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	free_table(game->table);
	copy_table(game->table_copy, &game->table);
	init_game(game);
}

/* Frees the tables and exits the program. */
int	exit_game(t_game *game)
{
	printf("closing...\n");
	printf("game->image_load_success %d\n", game->image_load_success);
	if (game->table)
		free_table(game->table);
	if (game->table_copy)
		free_table(game->table_copy);
	if (game->window.win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window.win_ptr);
	if (game->image_load_success)
	{
		mlx_destroy_image(game->mlx_ptr, game->images.wall);
		mlx_destroy_image(game->mlx_ptr, game->images.coll);
		mlx_destroy_image(game->mlx_ptr, game->images.exit);
		mlx_destroy_image(game->mlx_ptr, game->images.player1);
		mlx_destroy_image(game->mlx_ptr, game->images.player2);
		mlx_destroy_image(game->mlx_ptr, game->images.player3);
		mlx_destroy_image(game->mlx_ptr, game->images.player_end);
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
}
