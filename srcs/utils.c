/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:24 by facundo           #+#    #+#             */
/*   Updated: 2023/04/17 23:16:11 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	free_table(char **tab)
{
    int	i;
	
	i= 0;
    if (!tab)
		return;
    while (tab[i])
        free(tab[i++]);
   	free(tab);
}

char **copy_table(t_game *game) {
    int i;
    int j;
    int rows;
    int cols;
    char **new_table;

    i = 0;
    rows = game->map.rows + 1;
    cols = game->map.cols + 1;
    new_table = ft_calloc(rows, sizeof(char *));
    if (!new_table)
        handle_error(game, MALLOC_ERROR);
    while (i < rows) {
        new_table[i] = ft_strdup(game->table[i]);
		i++;
    }
    print_table(new_table);
    return new_table;
}

int	exit_game(t_game *game)
{
	char	**tmp;
	
	printf("closing...");
	if (game->table)
		free_table(game->table);
	if (game->window.win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window.win_ptr);
	exit(0);
}

void	reset_player_location(t_game *game, int i, int j)
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

int	open_and_check(int fd, char *file_path, t_game *game)
{
    fd = open(file_path, O_RDONLY);
	if (fd == -1)
		handle_error(game, strerror(errno));
}
