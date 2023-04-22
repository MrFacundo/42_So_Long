/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:49:03 by facundo           #+#    #+#             */
/*   Updated: 2023/04/22 16:17:37 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

/*Performs main checks and initializes game, path check and reset tables*/
void	validate_arg(int argc, char *argv, t_game *game)
{
	if (argc != 2)
		handle_error(game, BAD_ARGS);
	if (!extension_is_valid(argv))
		handle_error(game, BAD_EXTENSION);
	if (!map_is_valid(argv, game))
		handle_error(game, BAD_ELEMENTS);
	print_map_validation(game);
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
	if (!extension || ft_strncmp(extension, ".ber", 4))
		return (0);
	return (1);
}

/*Initializes and checks map data*/
int	map_is_valid(char *map_file_path, t_game *game)
{
	int		fd;
	int		i;
	char	*row;
	char	*trimmed_row;

	set_map_rows(map_file_path, game);
	fd = get_fd(map_file_path, game);
	i = 1;
	row = 0;
	row = ft_get_next_line(fd);
	while (row)
	{
		trimmed_row = ft_strtrim(row, "\n\r");
		free(row);
		check_row(trimmed_row, i++, game);
		free(trimmed_row);
		row = ft_get_next_line(fd);
	}
	close(fd);
	if (!game->map.collectable_count
		|| game->map.exit_count != 1
		|| game->map.player_count != 1)
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
	free_table(&game->table_copy);
	printf("requirements[0]: %d\n", requirements[0]);
	printf("requirements[1]: %d\n", requirements[1]);
	if (!requirements[0] || requirements[1] != game->map.collectable_count)
		return (0);
	return (1);
}

int	flood_fill(char **table, int y, int x, int *requirements)
{
	if (table[y][x] == '1' || table[y][x] == 'V')
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
