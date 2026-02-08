#include "cub3d.h"


int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*extension;
	char	*line;

	(void)game;  // TODO: usar game cuando se parsee
	
	extension = ft_strrchr(filename, '.');//sacamos la cadena cuando encuentra el caracter pero desde el final
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("File must have .cub extension");
		return (1);
	}

	// Abrir archivo
	// fd = open(filename, O_RDONLY);
	// if (fd < 0)
	// {
	// 	print_error("Cannot open file");
	// 	return (1);
	// }

	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	// TODO: Parsear línea por línea
	// TODO: Identificar texturas (NO, SO, WE, EA)
	// TODO: Identificar colores (F, C)
	// TODO: Leer mapa

	close(fd);
	return (0);
}
