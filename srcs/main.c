/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:28:22 by facundo           #+#    #+#             */
/*   Updated: 2023/04/23 22:02:21 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_program(&game);
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
	printf("reset game\n");
	mlx_clear_window(game->mlx_ptr, game->window.win_ptr);
	free_table(&game->table);
	copy_table(game->table_copy, &game->table);
	init_game(game);
}

void	destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->images.wall);
	mlx_destroy_image(game->mlx_ptr, game->images.coll);
	mlx_destroy_image(game->mlx_ptr, game->images.exit);
	mlx_destroy_image(game->mlx_ptr, game->images.player1);
	mlx_destroy_image(game->mlx_ptr, game->images.player2);
	mlx_destroy_image(game->mlx_ptr, game->images.player3);
	mlx_destroy_image(game->mlx_ptr, game->images.player_end);
	mlx_destroy_image(game->mlx_ptr, game->images.enemy1);
	mlx_destroy_image(game->mlx_ptr, game->images.enemy2);
}

/* Frees the tables and exits the program. */
int	exit_game(t_game *game)
{
	printf("closing...\n");
	if (game->table)
		free_table(&game->table);
	if (game->table_copy)
		free_table(&game->table_copy);
	if (game->window.win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window.win_ptr);
	if (game->image_load_success)
		destroy_images(game);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->enemies)
		free(game->enemies);
	exit(0);
}
