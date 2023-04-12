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

int map_is_valid(char *map_file_path, t_program *program)
{
	int i;
	char *line;
	int fd;
	int line_length;

	i = 1;
	fd = open(map_file_path, O_RDONLY);
	while (line = ft_get_next_line(fd))
	{
		line_length = (int)ft_strlen(line) - char_count(line, '\n');
		if (i == 1)
			program->map.cols = line_length;
		else if (line_length != program->map.cols)
		{
			program->map.diff = 1;
		}
		{
			program->map.collectable_count += char_count(line, 'C');
			program->map.exit_count += char_count(line, 'E');
			program->map.player_count += char_count(line, 'P');
		}
		i++;
	}
	program->map.rows = i;
	printf("i%d: line_length %d\n", i, line_length);
	printf("program->map.cols %d\n", program->map.cols);
	printf("program->map.diff %d\n", program->map.diff);
	printf("program->map.collectable_count %d\n", program->map.collectable_count);
	printf("program->map.exit_count %d\n", program->map.exit_count);
	printf("program->map.player_count %d\n", program->map.player_count);
	if (program->map.diff || !program->map.collectable_count || !program->map.exit_count || program->map.player_count != 1)
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