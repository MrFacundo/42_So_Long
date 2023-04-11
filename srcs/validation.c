#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/window.h"

int extension_is_valid(char *map_file_path)
{
	char	*extension;

	extension = ft_strrchr(map_file_path, '.');

	if (ft_strncmp(extension, ".ber", ft_strlen(extension)))
		return (0);
	return (1);
}

int validate_arg(int argc, char *argv)
{
	if (argc != 2)
	{
		printf("bad args m8");
		return (0);
	}
	if (!extension_is_valid(argv))
	{
		printf("bad extension m8");
		return (0);
	}
	return (1);
}