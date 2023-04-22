/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:24 by facundo           #+#    #+#             */
/*   Updated: 2023/04/22 17:16:35 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	free_table(char ***tab_ptr)
{
	char	**tab;
	int		i;

	tab = *tab_ptr;
	printf("freeing table\n");
	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	*tab_ptr = 0;
}

void	copy_table(char **src, char ***dst)
{
	int		rows;
	int		i;
	char	**table;

	rows = 0;
	i = 0;
	while (src[rows])
		rows++;
	table = ft_calloc(rows + 1, sizeof(char *));
	i = 0;
	while (src[i])
	{
		table[i] = ft_strdup(src[i]);
		i++;
	}
	*dst = table;
}

int	get_fd(char *file_path, t_game *game)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		handle_error(game, strerror(errno));
	return (fd);
}

void	reset_player_position(t_game *game, int i, int j)
{
	game->player.current.x = j;
	game->player.current.y = i;
	game->player.attempt.x = j;
	game->player.attempt.y = i;
}

void	handle_error(t_game *game, char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit_game(game);
}
