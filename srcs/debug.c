/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facundo <facundo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:50:25 by facundo           #+#    #+#             */
/*   Updated: 2023/04/20 16:14:55 by facundo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	print_table(char **table_ptr)
{
	int	i;

	i = 0;
	while (table_ptr[i])
		printf("%s", table_ptr[i++]);
	printf("\n\n");
}

void	print_map_validation(t_game *game)
{
	printf("game->map.rows %d\n", game->map.rows);
	printf("game->map.cols %d\n", game->map.cols);
	printf("game->map.diff %d\n", game->map.diff);
	printf("game->map.collectable_count %d\n", game->map.collectable_count);
	printf("game->map.exit_count %d\n", game->map.exit_count);
	printf("game->map.player_count %d\n", game->map.player_count);
	printf("game->map.invalid_char %d\n", game->map.invalid_char);
	printf("game->map.invalid_limits %d\n", game->map.invalid_limits);
}
