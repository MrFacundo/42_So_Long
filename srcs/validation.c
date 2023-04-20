/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facundo <facundo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:49:03 by facundo           #+#    #+#             */
/*   Updated: 2023/04/20 14:25:48 by facundo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

static int	flood_fill(char **table, int y, int x, int *requirements)
{
	if (table[y][x] == '1')
		return (0);
	else if (table[y][x] == 'C')
		requirements[1]++;
	else if (table[y][x] == 'E')
		requirements[0] = 1;
	table[y][x] = '1';
	flood_fill(table, y, x + 1, requirements);
	flood_fill(table, y, x - 1, requirements);
	flood_fill(table, y + 1, x, requirements);
	flood_fill(table, y - 1, x, requirements);
	return (0);
}

void	validate_arg(int argc, char *argv, t_game *game)
{
	if (argc != 2)
		handle_error(game, BAD_ARGS);
	if (!extension_is_valid(argv))
		handle_error(game, BAD_EXTENSION);
	if (!map_is_valid(argv, game))
		handle_error(game, BAD_ELEMENTS);
	init_table(argv, game);
	copy_table(game->table, &game->table_copy);
	if (!paths_are_valid(game))
		handle_error(game, BAD_PATH);
	copy_table(game->table, &game->table_copy);
}

int	extension_is_valid(char *map_file_path)
{
	char	*extension;

	extension = ft_strrchr(map_file_path, '.');
	printf("extension: %s\n", extension);
	if (!extension || ft_strncmp(extension, ".ber", 4 ))
		return (0);
	return (1);
}

int	map_is_valid(char *map_file_path, t_game *game)
{
	int		fd;
	int		i; 
	char	*row;

	fd = 0;
	row = 0;
	fd = open_and_check(fd, map_file_path, game);
	printf("row: %s\n", row);
	while (1)
	{
		row = ft_get_next_line(fd);
		if (!row)
			break;
		free(row);
		game->map.rows++;
	}
	if (row)
		free(row);
	close(fd);
	if (game->map.rows <3)
		handle_error(game, MAP_ROWS);
	open_and_check(fd, map_file_path, game);
	i = 1;
	row = 0;
	while (1)
	{
		row = ft_get_next_line(fd);
		if (!row)
			break;
		check_row(row, i++, game);
		free(row);
	}
	if (row)
		free(row);
	close(fd);
	print_map_validation(game);
	if (!game->map.collectable_count ||
		!game->map.exit_count ||
		game->map.player_count != 1)
		return (0);
	return (1);
}

int	paths_are_valid(t_game *game)
{
	int		x;
	int		y;
	int		requirements[2];

	y = game->player.current.y;
	x = game->player.current.x;
	requirements[0] = 0;
	requirements[1] = 0;
	flood_fill(game->table_copy, y, x, requirements);
	free_table(game->table_copy);
	printf("requirements[0]: %d\n", requirements[0]);
	printf("requirements[1]: %d\n", requirements[1]);
	if (!requirements[0] || requirements[1] != game->map.collectable_count)
		return (0);
	return (1);
}
