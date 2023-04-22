/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:12 by facundo           #+#    #+#             */
/*   Updated: 2023/04/22 17:13:09 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

static void	render_map_element(t_game *g, int i, int j, int *enemy_i)
{
	int	(*f)(void *, void *, void *, int x, int y);
	int	x;
	int	y;

	x = j * g->px;
	y = i * g->px;
	f = mlx_put_image_to_window;
	if (g->table[i][j] == WALL)
		f(g->mlx_ptr, g->window.win_ptr, g->images.wall, x, y);
	else if (g->table[i][j] == COLL)
		f(g->mlx_ptr, g->window.win_ptr, g->images.coll, x, y);
	else if (g->table[i][j] == EXIT)
		f(g->mlx_ptr, g->window.win_ptr, g->images.exit, x, y);
	else if (g->table[i][j] == ENEMY)
	{
		(*enemy_i)++;
		printf("enemy_i: %d\n", *enemy_i);
		reset_enemy_position(g, i, j, *enemy_i);
		f(g->mlx_ptr, g->window.win_ptr, g->images.enemy, x, y);
	}
	else if (g->table[i][j] == PLAYER)
	{
		reset_player_position(g, i, j);
		f(g->mlx_ptr, g->window.win_ptr, g->images.player, x, y);
	}
}

void	render_map(t_game *g)
{
	int	i;
	int	j;
	int	enemy_i;

	enemy_i = -1;
	i = -1;
	while (++i < g->map.rows)
	{
		j = -1;
		while (++j < g->map.cols)
			render_map_element(g, i, j, &enemy_i);
	}
}

void	render_counters(t_game *g)
{
	char	*move_count;
	char	*collectable_count;
	int		(*f)(void *, void *, int x, int y, int color, char *str);
	int		color;
	int		x;

	f = mlx_string_put;
	color = YELLOW;
	x = g->window.size.x - g->px / 2;
	move_count = ft_itoa(g->player.moves);
	collectable_count = ft_itoa(g->player.collected);
	f(g->mlx_ptr, g->window.win_ptr, x, g->px / 2, color, move_count);
	f(g->mlx_ptr, g->window.win_ptr, x, g->px, color, collectable_count);
	free(move_count);
	free(collectable_count);
}

void	render_win_message(t_game *g)
{
	int		(*f)(void *, void *, int x, int y, int color, char *str);
	int		x;
	int		y;
	char	*message;

	message = WIN_MSG;
	f = mlx_string_put;
	x = g->window.size.x / 2 - g->px * 2;
	y = g->window.size.y / 2 - g->px / 2;
	f(g->mlx_ptr, g->window.win_ptr, x, y, YELLOW, message);
	message = RESET_MSG_1;
	y += g->px;
	f(g->mlx_ptr, g->window.win_ptr, x, y, YELLOW, message);
}

void	render_lose_message(t_game *g)
{
	int		(*f)(void *, void *, int x, int y, int color, char *str);
	int		(*f2)(void *, void *, void *, int x, int y);
	int		x;
	int		y;
	char	*message;

	f = mlx_string_put;
	f2 = mlx_put_image_to_window;
	message = LOSE_MSG;
	x = g->window.size.x / 2 - g->px * 2;
	y = g->window.size.y / 2 - g->px / 2;
	f(g->mlx_ptr, g->window.win_ptr, x, y, YELLOW, message);
	message = RESET_MSG_2;
	y += g->px;
	f(g->mlx_ptr, g->window.win_ptr, x, y, YELLOW, message);
	x += g->px + g->px / 2;
	y += g->px / 2;
	f2(g->mlx_ptr, g->window.win_ptr, g->images.player_end, x, y);
}

/* Uses mlx_string_put() and mlx_put_image_to_window()
	to render a game over screen. The screen varies
	depending on how many collectibles were collected */
void	render_game_over_message(t_game *g, int condition)
{
	g->game_over = 1;
	mlx_clear_window(g->mlx_ptr, g->window.win_ptr);
	if (condition == 1 && g->player.collected == g->map.collectable_count)
		render_win_message(g);
	else
		render_lose_message(g);
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
