/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 20:30:21 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 19:33:06 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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


static int validate_and_open(char *filename)
{
	int	fd;	
	char	*extension;
	
	extension = ft_strrchr(filename, '.');  // Busca el último '.' en el nombre
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("File must have .cub extension");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (-1);
	}
	return (fd);
}

static int read_cub_lines(int fd, t_game *game)
{
	char	*line;
	
	while ((line = get_next_line(fd)) != NULL)
	{
		// Verificar si es el inicio del mapa
		if (is_map_line(line))
		{
			// Parsear el mapa (resto del archivo)
			if (parse_map(fd, line, game) != 0)
			{
				free(line);
				close(fd);
				return (1);
			}
			free(line);
			break;  // Ya leímos el mapa, salimos del loop
		}
		// Procesar la línea (texturas/colores)
		if (process_line(line, game) != 0)
		{
			// Si hay error, liberar memoria y salir
			free(line);
			close(fd);
			free_texture_paths(game);  // ← AÑADIR ESTA LÍNEA si falla liberamos todas las texturas
			return (1);
		}
		free(line);  // GNL asigna memoria, hay que liberarla
	}
	return (0);
}
static int validated_parsed_data(t_game *game)
{
	if (game->floor.r == -1 || game->ceiling.r == -1)
	{
		print_error("Missing color(s) - Floor (F) and Ceiling (C) required");
		return (1);
	}
	
	// 7. Verificar que se leyó el mapa
	if (!game->map.grid || game->map.height == 0)
	{
		print_error("Missing or invalid map");
		return (1);
	}
	
	// 8. Buscar la posición del jugador (N/S/E/W) en el mapa
	if (find_player(game) != 0)
		return (1);

		// 9. Verificar que el mapa esté cerrado por muros
	if (validate_map_walls(game) != 0)
		return (1);
	
	// Debug: mostrar info parseada
	printf("✅ Parseo completado:\n");
	printf("  Texturas: NO=%s SO=%s WE=%s EA=%s\n", 
		game->textures.north, game->textures.south,
		game->textures.west, game->textures.east);
	printf("  Floor: RGB(%d,%d,%d)  Ceiling: RGB(%d,%d,%d)\n",
		game->floor.r, game->floor.g, game->floor.b,
		game->ceiling.r, game->ceiling.g, game->ceiling.b);
	printf("  Mapa: %d líneas, ancho máximo: %d\n", game->map.height, game->map.width);
	printf("  Primera línea del mapa: [%s]\n", game->map.grid[0]);
	printf("  Última línea del mapa: [%s]\n", game->map.grid[game->map.height - 1]);
	
	return (0);
}

int	parse_cub_file(char *filename, t_game *game)
{
	int	fd;
	
	init_game_default(game);
	fd = validate_and_open(filename);
	if (fd < 0)
		return (1);
	if (read_cub_lines(fd, game) != 0)
	{
		close(fd);
		return (1);
	}
	close (fd);
	return (validated_parsed_data(game));

}