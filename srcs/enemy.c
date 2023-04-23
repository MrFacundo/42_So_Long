/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:33:06 by facundo           #+#    #+#             */
/*   Updated: 2023/04/23 22:41:22 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	move_enemy_in_direction(t_game *g, t_enemy *enemy, int dy, int dx)
{
	if (g->table[enemy->current.y + dy][enemy->current.x + dx] == '0')
	{
		g->table[enemy->current.y + dy][enemy->current.x + dx] = 'V';
		g->table[enemy->current.y][enemy->current.x] = '0';
	}
}

void	move_enemies(t_game *g)
{
	int		i;
	t_enemy	enemy;

	i = -1;
	if (g->player.moves % 3 == 0)
		return ;
	while (++i < g->map.enemy_count)
	{
		enemy = g->enemies[i];
		if (g->player.current.y > enemy.current.y)
			move_enemy_in_direction(g, &enemy, 1, 0);
		else if (g->player.current.y < enemy.current.y)
			move_enemy_in_direction(g, &enemy, -1, 0);
		else if (g->player.current.x > enemy.current.x)
			move_enemy_in_direction(g, &enemy, 0, 1);
		else if (g->player.current.x < enemy.current.x)
			move_enemy_in_direction(g, &enemy, 0, -1);
	}
}

void	init_enemies(t_game *game)
{
	t_enemy	*enemies;

	if (!game->map.enemy_count)
		return ;
	enemies = ft_calloc(game->map.enemy_count, sizeof(t_enemy));
	if (!enemies)
		handle_error(game, MALLOC_ERROR);
	game->enemies = enemies;
}

int	reset_enemy_position(t_game *game, int i, int j, int k)
{
	game->enemies[k].current.y = i;
	game->enemies[k].current.x = j;
	printf("enemy %d position reset to %d, %d\n", k, i, j);
	return (1);
}
