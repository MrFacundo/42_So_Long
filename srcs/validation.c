#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

void	check_characters(char *row, int row_number, t_program *program)
{
	int i;

	i = 0;
	while (row[i])
	{
		if (row[i] == 'C')
			program->map.collectable_count++;
		else if (row[i] == 'E')
			program->map.exit_count++;
		else if (row[i] == 'P')
		{
			program->player.current.y = row_number - 1;
			program->player.current.x = i;
			printf("Player y, x: %d, %d", program->player.current.y, program->player.current.x);
			program->map.player_count++;
		}
		else if (row[i] == '0' || row[i] == '1' || row[i] == '\n')
			;
		else
		{
			printf("Invalid character: %c\n", row[i]);
			program->map.invalid_char = 1;
		}
		i++;
	}
}

void	check_length(char *row, int row_number, t_program *program)
{
	int has_newline;
	int cols;

	has_newline = ft_strchr(row, '\n') ? 1 : 0;
	cols = (int)ft_strlen(row) - has_newline;
	if (row_number == 1)
		program->map.cols = cols;
	else if (cols != program->map.cols)
		program->map.diff = 1;
}

void check_limits(char *row, int row_number, t_program *program)
{
	if (row_number == 1 || row_number == program->map.rows)
		while (*row)
		{
			if (*row != WALL && *row != '\n')
				program->map.invalid_limits = 1;
			row++;
		}
	else if (row[0] != WALL || row[program->map.cols - 1] != WALL && row[program->map.cols - 1] != '\n')
		program->map.invalid_limits = 1;
}

void check_row(char *row, int row_number, t_program *program)
{
    check_length(row, row_number, program);
	if (program->map.diff)
		handle_error(program, MAP_SHAPE);
    check_characters(row, row_number, program);
	if (program->map.invalid_char)
		handle_error(program, MAP_CHAR);
    check_limits(row, row_number, program);
	if (program->map.invalid_limits)
		handle_error(program, MAP_LIMITS);
}


int map_is_valid(char *map_file_path, t_program *program)
{
    int fd, i;
    char *line;

    fd = open(map_file_path, O_RDONLY);
	if (fd == -1)
		handle_error(program, strerror(errno));
    while (line = ft_get_next_line(fd))
    {
        free(line);
        program->map.rows++;
    }
    close(fd);
    fd = open(map_file_path, O_RDONLY);
	if (fd == -1)
		handle_error(program, strerror(errno));
    i = 1;
    while (line = ft_get_next_line(fd))
	{
		check_row(line, i++, program);
		free(line);
	}
    close(fd);
    print_map_validation(program);
    if (!program->map.collectable_count ||
        !program->map.exit_count ||
        program->map.player_count != 1)
        return (0);
    return (1);
}

int extension_is_valid(char *map_file_path)
{
	char	*extension;

	extension = ft_strrchr(map_file_path, '.');
	printf("extension: %s\n", extension);
	if (ft_strncmp(extension, ".ber", 4 ))
		return (0);
	return (1);
}

int	flood_fill(char **lines, int y, int x, int *requirements)
{
	if (lines[y][x] == '1')
		return (0);
	else if (lines[y][x] == 'C')
		requirements[1]++;
	else if (lines[y][x] == 'E')
		requirements[0] = 1;
	lines[y][x] = '1';
	flood_fill(lines, y, x + 1, requirements);
	flood_fill(lines, y, x - 1, requirements);
	flood_fill(lines, y + 1, x, requirements);
	flood_fill(lines, y - 1, x, requirements);
	return (0);
}

int	paths_are_valid(t_program *program)
{
	int		x;
	int		y;
	int		requirements[2];

	y = program->player.current.y;
	x = program->player.current.x;
	requirements[0] = 0;
	requirements[1] = 0;
	flood_fill(program->lines_copy, y, x, requirements);
	// ft_free_tab(flood_map, -1);
	if (!requirements[0])
		return (0);
	// if ( != game->map->totalcoins)
	// 	handle_error(program, BAD_ELEMENTS);
}

void validate_arg(int argc, char *argv, t_program *program)
{
	if (argc != 2)
		handle_error(program, BAD_ARGS);
	if (!extension_is_valid(argv))
		handle_error(program, BAD_EXTENSION);
	if (!map_is_valid(argv, program))
		handle_error(program, BAD_ELEMENTS);
	init_lines(argv, program, &program->lines);
	init_lines(argv, program, &program->lines_copy);
	if (!paths_are_valid(program))
		handle_error(program, BAD_PATH);
	print_lines(program->lines_copy);
	print_lines(program->lines);

}