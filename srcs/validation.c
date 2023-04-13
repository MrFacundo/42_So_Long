#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/so_long.h"

int	char_count(char *str, int c)
{
	int count;

	count = 0;
	while (*str)
		if (*str++ == c)
			count++;
	return (count);
}

void	check_characters(char *line, t_program *program)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			program->map.collectable_count++;
		else if (line[i] == 'E')
			program->map.exit_count++;
		else if (line[i] == 'P')
			program->map.player_count++;
		else if (line[i] == '0' || line[i] == '1' || line[i] == '\n')
			;
		else
		{
			printf("Invalid character: %c\n", line[i]);
			program->map.invalid_char = 1;
		}
		i++;
	}
}

void	check_length(char *line, int line_number, t_program *program)
{
	int has_newline;
	int line_length;

	has_newline = ft_strchr(line, '\n') ? 1 : 0;
	line_length = (int)ft_strlen(line) - has_newline;
	if (line_number == 1)
		program->map.cols = line_length;
	else if (line_length != program->map.cols)
		program->map.diff = 1;
}

void check_limits(char *line, int line_number, t_program *program)
{
	if (line_number == 1 || line_number == program->map.rows)
		while (*line)
		{
			if (*line != WALL && *line != '\n')
			{
				printf("*line: %c\n", *line);
				program->map.invalid_limits = 1;
			}
			line++;
		}
	else if (line[0] != WALL || line[program->map.cols - 1] != WALL && line[program->map.cols - 1] != '\n')
	{
		printf("line[0]: %c\n", line[0]);
		printf("line[program->map.cols - 1]: %c\n", line[program->map.cols - 1]);
		program->map.invalid_limits = 1;
	}
}

void check_map_line(char *line, int line_number, t_program *program)
{
    check_length(line, line_number, program);
    check_characters(line, program);
    check_limits(line, line_number, program);
}


int map_is_valid(char *map_file_path, t_program *program)
{
    int fd, i;
    char *line;

    fd = open(map_file_path, O_RDONLY);
    while (line = ft_get_next_line(fd))
    {
        free(line);
        program->map.rows++;
    }
    close(fd);
    fd = open(map_file_path, O_RDONLY);
    i = 1;
    while (line = ft_get_next_line(fd))
	{
		check_map_line(line, i++, program);
		free(line);
	}
    close(fd);
    print_map_validation(program);
    if (program->map.diff ||
        program->map.invalid_char ||
        program->map.invalid_limits ||
        !program->map.collectable_count ||
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
	if (ft_strncmp(extension, ".ber", ft_strlen(extension)))
		return (0);
	return (1);
}

void validate_arg(int argc, char *argv, t_program *program)
{
	if (argc != 2)
		exit_program(program, "bad args m8");
	if (!extension_is_valid(argv))
		exit_program(program, "bad extension m8");
	if (!map_is_valid(argv, program))
		exit_program(program, "invalid map m8");
}