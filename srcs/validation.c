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

void validate_arg(int argc, char *argv, t_program *program)
{
	if (argc != 2)
		handle_error(program, BAD_ARGS);
	if (!extension_is_valid(argv))
		handle_error(program, BAD_EXTENSION);
	if (!map_is_valid(argv, program))
		handle_error(program, BAD_ELEMENTS);
}