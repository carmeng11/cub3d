#include "cub3d.h"
/*

Esta función identifica el tipo de línea (textura, color o mapa) y la procesa.
pueden haber espacios al inicio, por eso los saltamos primero
@line: Línea leída del archivo .cub
@game: Estructura del juego donde guardamos la info parseadda
Return: 0 si OK, 1 si error
*/

static int	process_line(char *line, t_game *game)
{
	int i;
	
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.north));
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.south));
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.west));
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.east));
	
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (parse_color_line(&line[i + 2], &game->floor));
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (parse_color_line(&line[i + 2], &game->ceiling));
	
	
	return (0);
}
/*
parse_cub_file - Función principal de parseo del archivo .cub
1. Verificar extensión .cub
2. Abrir archivo
3. Leer línea por línea con GNL
4. Procesar cada línea (identificar tipo y parsear)
5. Validar que se obtuvieron todos los elementos obligatorios
@filename: Ruta al archivo .cub (argv[1])
@game: Estructura del juego donde se guardan los datos parseados
Return: 0 si OK, 1 si error
*/


int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*extension;
	char	*line;

	// 1. Inicializar texturas a NULL para poder detectar si faltan después
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	
	// Inicializar colores a -1 para detectar si faltan
	// (los valores válidos son 0-255, así que -1 indica "no parseado")
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	
	// 2. Validar que el archivo tiene extensión .cub (requisito del subject)
	extension = ft_strrchr(filename, '.');  // Busca el último '.' en el nombre
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("File must have .cub extension");
		return (1);
	}

	// 3. Abrir archivo en modo solo lectura
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (1);
	}

	// 4. Leer el archivo línea por línea con get_next_line
	while ((line = get_next_line(fd)) != NULL)
	{
		// Procesar la línea (identifica si es textura, color o mapa)
		if (process_line(line, game) != 0)
		{
			// Si hay error, liberar memoria y salir
			free(line);
			close(fd);
			return (1);
		}
		free(line);  // GNL asigna memoria, hay que liberarla
	}

	close(fd);
	
	// 5. Verificar que se leyeron TODAS las texturas (obligatorias según subject)
	//    Si alguna es NULL, significa que faltó en el archivo
	if (!game->textures.north || !game->textures.south ||
		!game->textures.west || !game->textures.east)
	{
		print_error("Missing texture(s)");
		return (1);
	}
	
	// 6. Verificar que se leyeron los colores (obligatorios según subject)
	//    Si algún componente sigue en -1, faltó el color
	if (game->floor.r == -1 || game->ceiling.r == -1)
	{
		print_error("Missing color(s) - Floor (F) and Ceiling (C) required");
		return (1);
	}
	
	return (0);
}
