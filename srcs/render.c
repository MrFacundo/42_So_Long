/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:12 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 18:26:26 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	render_map_element(t_game *g, int i, int j)
{
	int	(*f)(void *, void *, void *, int x, int y);
	int	x;
	int	y;

	x = j * g->px;
	y = i * g->px;
	f = mlx_put_image_to_window;
	if (g->table[i][j] == WALL)
		f(g->mlx_ptr, g->window.win_ptr, g->images.wall, x, y);
	else if (g->table[i][j] == FLOOR)
		f(g->mlx_ptr, g->window.win_ptr, g->images.floor, x, y);
	else if (g->table[i][j] == COLLECTABLE)
		f(g->mlx_ptr, g->window.win_ptr, g->images.coll, x, y);
	else if (g->table[i][j] == EXIT)
		f(g->mlx_ptr, g->window.win_ptr, g->images.exit, x, y);
	else if (g->table[i][j] == PLAYER)
	{
		reset_player_location(g, i, j);
		f(g->mlx_ptr, g->window.win_ptr, g->images.player, x, y);
	}
}

void	render_map(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->map.rows)
	{
		j = -1;
		while (++j < g->map.cols)
			render_map_element(g, i, j);
	}
}

void	render_counters(t_game *g)
{
	char	*move_count;
	char	*collectable_count;
	char	(*f)(void *, void *, int x, int y, int color, char *str);
	int	color;
	int		x;

	f = mlx_string_put;
	color = 0x008fce00;
	x = g->window.size.x - 12;
	move_count = ft_itoa(g->player.moves);
	collectable_count = ft_itoa(g->player.collectable);
	f(g->mlx_ptr, g->window.win_ptr, x, 12, color, move_count);
	f(g->mlx_ptr, g->window.win_ptr, x, 24, color, collectable_count);
	free(move_count);
	free(collectable_count);
}
