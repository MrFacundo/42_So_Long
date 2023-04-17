/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:23:36 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 22:33:52 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

// t_img	new_img(int width, int height, t_game *game)
// {
// 	t_img	image;

// 	image.window = game->window;
// 	image.img_ptr = mlx_new_image(game->mlx_ptr, width, height);
// 	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
// 			&(image.line_len), &(image.endian));
// 	image.width = width;
// 	image.height = height;
// 	return (image);
// }

// void	render_background(t_game *game)
// {
// 	t_img	image;
// 	int height;
// 	int width;

// 	height = game->window.size.y;
// 	width = game->window.size.x;
// 	image = new_img(width, height, game);
// 	mlx_put_image_to_window(game->mlx_ptr, game->window.win_ptr,
// 		image.img_ptr, 0, 0);
// }

// int	**new_table(int rows, int cols, char c, t_game *game)
// {
// 	int	**table;
// 	int	i;
// 	int	j;

// 	table = (int **)malloc(sizeof(int *) * rows);
// 	if (!table)
// 		handle_error(game, MALLOC_ERROR);
// 	i = -1;
// 	while (++i < rows)
// 	{
// 		table[i] = (int *)malloc(sizeof(int) * cols);
// 		if (!table[i])
// 		handle_error(game, MALLOC_ERROR);
// 		j = -1;
// 		while (++j < cols)
// 			table[i][j] = c;
// 	}
// 	printf("new table:\n");
// 	print_table(*table);
// 	return (table);
// }

void	render_game_over_message(t_game *g)
{
	char	(*f)(void *, void *, int x, int y, int color, char *str);
	int	color;
	int		x;
	int		y;
	char	*message;

	g->game_over = 1;
	mlx_clear_window(g->mlx_ptr, g->window.win_ptr);
	if (g->player.collected == g->map.collectable_count)
		message = "You win!";
	else
		message = "Game Over";
	f = mlx_string_put;
	color = 0x008fce00;
	x = g->window.size.x /2;
	y = g->window.size.y /2;
	f(g->mlx_ptr, g->window.win_ptr, x, y, color, message);
}

void	reset_game(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	//init_table(argv, game, &game->table);
	init_game(game);
}