/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facundo <facundo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:08:24 by ftroiter          #+#    #+#             */
/*   Updated: 2023/04/24 16:27:15 by facundo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

static void	check_img_pointers(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (!g->images.all_ptrs[i])
			handle_error(g, IMG_ERROR);
	}
}

/* Create images array to allow programatical checks and freeing*/
static int	init_img_array(t_game *g)
{
	g->images.all_ptrs[0] = g->images.wall;
	g->images.all_ptrs[1] = g->images.coll;
	g->images.all_ptrs[2] = g->images.exit;
	g->images.all_ptrs[3] = g->images.player1;
	g->images.all_ptrs[4] = g->images.player2;
	g->images.all_ptrs[5] = g->images.player3;
	g->images.all_ptrs[6] = g->images.enemy1;
	g->images.all_ptrs[7] = g->images.enemy2;
	return (0);
}

/* Creates pointers for the all images needed by the game */
void	init_images(t_game *g)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	g->images_initialized = 1;
	g->images.wall = f(g->mlx_ptr, "xpm/wall.xpm", &g->px, &g->px);
	g->images.coll = f(g->mlx_ptr, "xpm/coll.xpm", &g->px, &g->px);
	g->images.exit = f(g->mlx_ptr, "xpm/exit.xpm", &g->px, &g->px);
	g->images.player1 = f(g->mlx_ptr, "xpm/p1.xpm", &g->px, &g->px);
	g->images.player2 = f(g->mlx_ptr, "xpm/p2.xpm", &g->px, &g->px);
	g->images.player3 = f(g->mlx_ptr, "xpm/pcoll.xpm", &g->px, &g->px);
	g->images.player_end = f(g->mlx_ptr, "xpm/p_end.xpm", &g->px, &g->px);
	g->images.player = g->images.player1;
	g->images.enemy1 = f(g->mlx_ptr, "xpm/vs1.xpm", &g->px, &g->px);
	g->images.enemy2 = f(g->mlx_ptr, "xpm/vs2.xpm", &g->px, &g->px);
	g->images.enemy = g->images.enemy1;
	init_img_array(g);
	check_img_pointers(g);
}
