#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void print_lines(t_program *program)
{
	int i;

	i = 0;
    while (program->lines[i])
        printf("%s", program->lines[i++]);
	printf("\n\n");
}

void print_map_validation(t_program *program)
{
	printf("program->map.rows %d\n", program->map.rows);
	printf("program->map.cols %d\n", program->map.cols);
	printf("program->map.diff %d\n", program->map.diff);
	printf("program->map.collectable_count %d\n", program->map.collectable_count);
	printf("program->map.exit_count %d\n", program->map.exit_count);
	printf("program->map.player_count %d\n", program->map.player_count);
	printf("program->map.invalid_char %d\n", program->map.invalid_char);
	printf("program->map.invalid_limits %d\n", program->map.invalid_limits);
}