/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:28:22 by facundo           #+#    #+#             */
/*   Updated: 2023/04/25 20:19:15 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_program_data(&game);
	validate_arg(argc, argv[1], &game);
	game.mlx_ptr = mlx_init();
	game.window = init_window(game, "so long");
	init_images(&game);
	init_game(&game);
	return (0);
}

/* Initializes game contect variables, renders images
	and hooks key input to mlx_loop */
void	init_game(t_game *game)
{
	game->game_over = 0;
	game->player.collected = 0;
	game->player.moves = 0;
	init_enemies(game);
	render_map(game);
	mlx_key_hook(game->window.win_ptr, handle_key, game);
	mlx_loop(game->mlx_ptr);
}

/* Clears the window, resets the table and re-initializes the game. */
void	reset_game(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	free_table(&game->table);
	copy_table(game->table_copy, &game->table);
	init_game(game);
}

void	destroy_images(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 8)
		mlx_destroy_image(game->mlx_ptr, game->images.all_ptrs[i]);
}

/* Frees memory and exits the program. */
int	exit_game(t_game *game)
{
	if (game->table)
		free_table(&game->table);
	if (game->table_copy)
		free_table(&game->table_copy);
	if (game->enemies)
		free(game->enemies);
	if (game->window.win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window.win_ptr);
	if (game->images_initialized)
		destroy_images(game);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
}
