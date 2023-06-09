/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facundo <facundo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:49:24 by facu              #+#    #+#             */
/*   Updated: 2023/04/24 16:45:49 by facundo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

static void	handle_movement_key(int keycode, t_game *game)
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
		return ;
	if (game->table[game->player.attempt.y][game->player.attempt.x] != WALL)
	{
		move_player(game);
		if (game->map.enemy_count)
			move_enemies(game);
	}
	else
	{
		game->player.attempt.x = game->player.current.x;
		game->player.attempt.y = game->player.current.y;
	}
}

/* Input management. Called each time a key is pressed. */
int	handle_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == RESET1 || keycode == RESET2)
		reset_game(game);
	if (!game->game_over)
		handle_movement_key(keycode, game);
	return (0);
}

/* Move the player to the next position. */
void	move_player(t_game *g)
{	
	if (g->table[g->player.attempt.y][g->player.attempt.x] == COLL)
		g->player.collected += 1;
	else if (g->table[g->player.attempt.y][g->player.attempt.x] == EXIT
			|| g->table[g->player.attempt.y][g->player.attempt.x] == ENEMY)
	{
		g->game_over = 1;
		render_game_over_message(g);
		render_counters(g);
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

void	animate(t_game *game)
{
	if (game->table[game->player.attempt.y][game->player.attempt.x] == COLL)
	{
		game->images.player = game->images.player3;
		return ;
	}	
	if (game->player.moves % 2 == 0)
		game->images.player = game->images.player1;
	else
		game->images.player = game->images.player2;
}
