/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:47:27 by facundo           #+#    #+#             */
/*   Updated: 2023/04/22 17:08:55 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

/* Initializes variables needed for validation and first render */
void	init_program(t_game *game)
{
	game->window.win_ptr = 0;
	game->mlx_ptr = 0;
	game->px = 32;
	game->table = 0;
	game->table_copy = 0;
	game->enemies = 0;
	game->image_load_success = 0;
	game->map.diff = 0;
	game->map.collectable_count = 0;
	game->map.exit_count = 0;
	game->map.invalid_char = 0;
	game->map.invalid_limits = 0;
	game->map.rows = 0;
	game->map.player_count = 0;
	game->map.enemy_count = 0;
}

/* Initializes game contect variables, renders images
	and hooks key input to mlx_loop */
void	init_game(t_game *game)
{
	game->player.collected = 0;
	game->player.moves = 0;
	game->game_over = 0;
	init_enemies(game);
	render_map(game);
	mlx_key_hook(game->window.win_ptr, handle_key, game);
	mlx_loop(game->mlx_ptr);
}

/* Creates window pointer and hooks ESC key input to mlx_hook */
t_window	init_window(t_game game, char *name)
{
	t_window	window;

	window.size.x = game.map.cols * game.px + game.px;
	window.size.y = game.map.rows * game.px;
	window.win_ptr = mlx_new_window(game.mlx_ptr,
			window.size.x,
			window.size.y,
			name);
	mlx_hook(window.win_ptr, 17, 0, exit_game, &game);
	return (window);
}

/* Creates a table or 2D array from the provided map file*/
void	init_table(char *map_file, t_game *game)
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
	table[i] = ft_get_next_line(fd);
	while (table[i])
		table[++i] = ft_get_next_line(fd);
	close(fd);
	game->table = table;
	printf("init table %p\n", game->table);
	print_table(game->table);
}
