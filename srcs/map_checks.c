/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:47:57 by facundo           #+#    #+#             */
/*   Updated: 2023/04/18 21:57:30 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	check_row(char *row, int row_number, t_game *game)
{
	check_length(row, row_number, game);
	if (game->map.diff)
		handle_error(game, MAP_SHAPE);
	check_characters(row, row_number, game);
	if (game->map.invalid_char)
		handle_error(game, MAP_CHAR);
	check_limits(row, row_number, game);
	if (game->map.invalid_limits)
		handle_error(game, MAP_LIMITS);
}

void	check_length(char *row, int row_number, t_game *game)
{
	int	cols;

	cols = (int)ft_strlen(row) - ft_strlen(ft_strchr(row, '\n'));
	if (row_number == 1)
		game->map.cols = cols;
	else if (cols != game->map.cols)
		game->map.diff = 1;
}

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
		else if (row[i] == 'P')
		{
			game->player.current.y = row_number - 1;
			game->player.current.x = i;
			game->map.player_count++;
			printf("Player position: %d, %d\n", game->player.current.y, game->player.current.x);
		}
		else if (row[i] == '0' || row[i] == '1' || row[i] == '\n')
			;
		else
		{
			printf("Invalid character: %c\n", row[i]);
			game->map.invalid_char = 1;
		}
		i++;
	}
}

void	check_limits(char *row, int row_number, t_game *game)
{
	if (row_number == 1 || row_number == game->map.rows)
		while (*row)
		{
			if (*row != WALL && *row != '\n')
				game->map.invalid_limits = 1;
			row++;
		}
	else if (row[0] != WALL
		|| row[game->map.cols - 1] != WALL
		&& row[game->map.cols - 1] != '\n')
		game->map.invalid_limits = 1;
}
