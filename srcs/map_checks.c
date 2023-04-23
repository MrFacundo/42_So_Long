/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:47:57 by facundo           #+#    #+#             */
/*   Updated: 2023/04/23 22:13:16 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

/* Sets the number of rows in the map and checks if it is valid */
void	set_map_rows(char *map_file_path, t_game *game)
{
	int		fd;
	char	*row;

	row = 0;
	fd = get_fd(map_file_path, game);
	row = ft_get_next_line(fd);
	while (row)
	{
		game->map.rows++;
		free(row);
		row = ft_get_next_line(fd);
	}
	close(fd);
	if (game->map.rows < 3)
		handle_error(game, MAP_LIMITS);
}

/* Perform checks on each row and sets game variables */
void	check_row(char *row, int row_number, t_game *game)
{
	check_length(row, row_number, game);
	if (game->map.diff)
		handle_error(game, MAP_SHAPE);
	check_limits(row, row_number, game);
	if (game->map.invalid_limits)
		handle_error(game, MAP_LIMITS);
	check_characters(row, row_number, game);
	if (game->map.invalid_char)
		handle_error(game, MAP_CHAR);
}

/* Checks if the map is rectangular */
void	check_length(char *row, int row_number, t_game *game)
{
	int	cols;

	cols = (int)ft_strlen(row);
	printf("cols: %d\n", cols);
	if (row_number == 1)
		game->map.cols = cols;
	else if (cols != game->map.cols)
		game->map.diff = 1;
}

/* Checks if the map has valid characters and sets player position*/
void	check_characters(char *row, int row_number, t_game *game)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == 'C')
			game->map.collectable_count++;
		else if (row[i] == 'E')
			game->map.exit_count++;
		else if (row[i] == 'V')
			game->map.enemy_count++;
		else if (row[i] == 'P')
		{
			game->player.current.y = row_number - 1;
			game->player.current.x = i;
			game->map.player_count++;
		}
		else if (row[i] == '0' || row[i] == '1' || row[i] == 'V')
			;
		else
			game->map.invalid_char = 1;
		i++;
	}
}

/* Checks if the map has valid borders */
void	check_limits(char *row, int row_number, t_game *game)
{
	if (row_number == 1 || row_number == game->map.rows)
	{
		while (*row)
		{
			if (*row != WALL)
				game->map.invalid_limits = 1;
			row++;
		}
	}
	else if (row[0] != WALL || row[game->map.cols - 1] != WALL)
		game->map.invalid_limits = 1;
}
