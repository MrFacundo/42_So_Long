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

void	line_check(char *line, t_program *program)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			program->map.collectable_count += 1;
		else if (line[i] == 'E')
			program->map.exit_count += 1;
		else if (line[i] == 'P')
			program->map.player_count += 1;
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

int map_is_valid(char *map_file_path, t_program *program)
{
	int i;
	char *line;
	int fd;
	int has_newline;
	int line_length;

	i = 0;
	fd = open(map_file_path, O_RDONLY);
	line = ft_get_next_line(fd);
	while (line && ++i)
	{
		has_newline = ft_strchr(line, '\n') ? 1 : 0;
		line_length = (int)ft_strlen(line) - has_newline;
		if (i == 1)
			program->map.cols = line_length;
		else if (line_length != program->map.cols)
			program->map.diff = 1;
		line_check(line, program);
		free(line);
		line = ft_get_next_line(fd);
	}
	program->map.rows = i;
	printf("program->map.rows %d\n", program->map.rows);
	printf("program->map.cols %d\n", program->map.cols);
	printf("program->map.diff %d\n", program->map.diff);
	printf("program->map.collectable_count %d\n", program->map.collectable_count);
	printf("program->map.exit_count %d\n", program->map.exit_count);
	printf("program->map.player_count %d\n", program->map.player_count);
	printf("program->map.invalid_char %d\n", program->map.invalid_char);
	if (program->map.diff
		|| program->map.invalid_char
		|| !program->map.collectable_count
		|| !program->map.exit_count
		|| program->map.player_count != 1)
		return (0);
	return (1);
}


int extension_is_valid(char *map_file_path)
{
	char	*extension;

	extension = ft_strrchr(map_file_path, '.');
	printf("extension: %s\n", extension);
	printf("ft_strncmp(extension, \".ber\", ft_strlen(extension) %d\n", ft_strncmp(extension, ".ber", ft_strlen(extension)));
	if (ft_strncmp(extension, ".ber", ft_strlen(extension)))
		return (0);
	return (1);
}

int validate_arg(int argc, char *argv, t_program *program)
{
	if (argc != 2)
		exit_program(program, "bad args m8");
	if (!extension_is_valid(argv))
		exit_program(program, "bad extension m8");
	if (!map_is_valid(argv, program))
		exit_program(program, "invalid map m8");
	return (1);
}