/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:47:27 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 19:01:49 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

t_window	init_window(t_game game, char *name)
{
	t_window	window;

	window.size.x = game.map.cols * game.px;
	window.size.y = game.map.rows * game.px;
	window.win_ptr = mlx_new_window(game.mlx_ptr,
			window.size.x,
			window.size.y,
			name);
	mlx_hook(window.win_ptr, 17, 0, exit_game, &game);
	return (window);
}

void	init_program(t_game *game)
{
	game->window.win_ptr = 0;
	game->px = 32;
	game->table = 0;
	game->map.diff = 0;
	game->map.collectable_count = 0;
	game->map.exit_count = 0;
	game->map.invalid_char = 0;
	game->map.invalid_limits = 0;

}

void	init_table(char *map_file, t_game *game, char ***table_ptr)
{
	char	**table;
	int		i;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		handle_error(game, strerror(errno));
	table = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!table)
		handle_error(game, MALLOC_ERROR);
	i = 0;
	while (table[i++] = ft_get_next_line(fd));
	close(fd);
	*table_ptr = table;
	print_table(*table_ptr);
}

void	init_images(t_game *game)
{
	game->images.floor = mlx_xpm_file_to_image(
			game->mlx_ptr,
			"xpm/floor.xpm",
			&game->px,
			&game->px);
	game->images.wall = mlx_xpm_file_to_image(
			game->mlx_ptr,
			"xpm/wall.xpm",
			&game->px,
			&game->px);
	game->images.coll = mlx_xpm_file_to_image(
			game->mlx_ptr,
			"xpm/collectable.xpm",
			&game->px,
			&game->px);
	game->images.exit = mlx_xpm_file_to_image(
			game->mlx_ptr,
			"xpm/exit.xpm",
			&game->px,
			&game->px);
	game->images.player = mlx_xpm_file_to_image(
			game->mlx_ptr,
			"xpm/player.xpm",
			&game->px,
			&game->px);
}
