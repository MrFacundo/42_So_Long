/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:08:24 by ftroiter          #+#    #+#             */
/*   Updated: 2023/04/22 17:08:55 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	init_player_images(t_game *g, void	*(*f)(void *, char *, int *, int *))
{
	g->images.player1 = f(g->mlx_ptr, "xpm/p1.xpm", &g->px, &g->px);
	if (!g->images.player1)
		handle_error(g, IMG_ERROR);
	g->images.player2 = f(g->mlx_ptr, "xpm/p2.xpm", &g->px, &g->px);
	if (!g->images.player2)
		handle_error(g, IMG_ERROR);
	g->images.player3 = f(g->mlx_ptr, "xpm/pcoll.xpm", &g->px, &g->px);
	if (!g->images.player3)
		handle_error(g, IMG_ERROR);
	g->images.player_end = f(g->mlx_ptr, "xpm/p_end.xpm", &g->px, &g->px);
	if (!g->images.player_end)
		handle_error(g, IMG_ERROR);
	g->images.player = g->images.player1;
}

void	init_enemy_images(t_game *g, void *(*f)(void *, char *, int *, int *))
{
	g->images.enemy1 = f(g->mlx_ptr, "xpm/vs1.xpm", &g->px, &g->px);
	if (!g->images.enemy1)
		handle_error(g, IMG_ERROR);
	g->images.enemy2 = f(g->mlx_ptr, "xpm/vs2.xpm", &g->px, &g->px);
	if (!g->images.enemy2)
		handle_error(g, IMG_ERROR);
	g->images.enemy = g->images.enemy1;
}

/* Creates pointers for the all images needed in the game */
void	init_images(t_game *g)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	g->images.wall = f(g->mlx_ptr, "xpm/wall.xpm", &g->px, &g->px);
	if (!g->images.wall)
		handle_error(g, IMG_ERROR);
	g->images.coll = f(g->mlx_ptr, "xpm/coll.xpm", &g->px, &g->px);
	if (!g->images.coll)
		handle_error(g, IMG_ERROR);
	g->images.exit = f(g->mlx_ptr, "xpm/exit.xpm", &g->px, &g->px);
	if (!g->images.exit)
		handle_error(g, IMG_ERROR);
	init_player_images(g, f);
	init_enemy_images(g, f);
	g->image_load_success = 1;
}
