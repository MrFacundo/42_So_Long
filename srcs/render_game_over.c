/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game_over.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:05:19 by facu              #+#    #+#             */
/*   Updated: 2023/04/23 22:05:55 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

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
