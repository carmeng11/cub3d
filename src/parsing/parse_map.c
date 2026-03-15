/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:11:39 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 19:34:25 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_map_line - Detecta si una línea pertenece al mapa
** 
** Una línea es del mapa si contiene: 1, 0, espacios, N, S, E, W
** (ignorando espacios iniciales)
**
** @line: Línea a verificar
** Return: 1 si es línea de mapa, 0 si no
*/
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	// Saltar espacios iniciales
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	
	// Si está vacía, no es mapa
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	
	// Si empieza con '1' o espacio seguido de contenido, es mapa
	if (line[i] == '1')
		return (1);
	
	return (0);
}

/*
** is_valid_char - Verifica si un carácter es válido SOLO PARA BORDE DE MAPA
** 
** Los bordes pueden tener '1' (muro) o espacios (exterior).
** NO pueden tener '0', 'N', 'S', 'E', 'W' (serían accesibles desde fuera)
**
** @c: Carácter a verificar
** Return: 1 si es válido para borde, 0 si no
*/
static int	is_valid_char(char c)
{
	return (c == '1' || c == ' ' || c == '\t');
}

/*
** validate_map_walls - Verifica que el mapa esté cerrado por muros
**
** Reglas del subject:
** - El mapa debe estar rodeado de muros ('1')
** - Los espacios en bordes son válidos (representan exterior)
** - NO puede haber '0' o jugador (N/S/E/W) en los bordes
**
** Verificación:
** 1. Primera fila: solo '1' y espacios
** 2. Última fila: solo '1' y espacios
** 3. Primera columna de cada fila: solo '1' o espacio
** 4. Última columna de cada fila: solo '1' o espacio
**
** @game: Estructura con el mapa ya parseado
** Return: 0 si OK, 1 si mapa no está cerrado
*/
int	validate_map_walls(t_game *game)
{
	int		y;
	int		x;
	char	**grid;

	grid = game->map.grid;
	
	// VERIFICAR PRIMERA FILA (y = 0)
	x = 0;
	while (grid[0][x])
	{
		if (!is_valid_char(grid[0][x]))
		{
			print_error("Map not closed: invalid char in first row");
			return (1);
		}
		x++;
	}
	
	// VERIFICAR ÚLTIMA FILA (y = height - 1)
	x = 0;
	while (grid[game->map.height - 1][x])
	{
		if (!is_valid_char(grid[game->map.height - 1][x]))
		{
			print_error("Map not closed: invalid char in last row");
			return (1);
		}
		x++;
	}
	
	// VERIFICAR PRIMERA Y ÚLTIMA COLUMNA DE CADA FILA
	y = 0;
	while (y < game->map.height)
	{
		// Primera columna (primer carácter no puede ser 0/N/S/E/W)
		if (!is_valid_char(grid[y][0]))
		{
			print_error("Map not closed: invalid char in first column");
			return (1);
		}
		
		// Última columna (último carácter de la línea)
		x = ft_strlen(grid[y]);
		if (x > 0 && !is_valid_char(grid[y][x - 1]))
		{
			print_error("Map not closed: invalid char in last column");
			return (1);
		}
		y++;
	}
	
	printf("Mapa cerrado correctamente por muros\n");
	return (0);
}



// Esta función identifica el tipo de línea (textura, color o mapa) y la procesa.
// pueden haber espacios al inicio, por eso los saltamos primero
// @line: Línea leída del archivo .cub
// @game: Estructura del juego donde guardamos la info parseadda
// Return: 0 si OK, 1 si error
// */



/*
** parse_map - Lee y guarda el mapa del archivo
**
** El mapa siempre es lo último del archivo (según subject).
** Lee todas las líneas restantes y las guarda en game->map.grid
**
** @fd: File descriptor del archivo ya abierto
** @first_line: Primera línea del mapa (ya leída)
** @game: Estructura donde guardar el mapa
**
** Return: 0 si OK, 1 si error
*/
// static int	parse_map(int fd, char *first_line, t_game *game)
// {
// 	// Despues del mapa no puede haber nada que no sea un carater valido como lo de arriba.


int	parse_map(int fd, char *first_line, t_game *game)
{
	char	**temp_map;
	char	*line;
	char	*trimmed;
	int		i;
	int		j;

	 // ═══════════════════════════════════════════════════════════
    // PASO 1: Preparar almacenamiento temporal
    // ═══════════════════════════════════════════════════════════
	temp_map = malloc(sizeof(char *) * 101);  // Máximo 100 líneas + NULL
	if (!temp_map)
		return (1);
	
	// ═══════════════════════════════════════════════════════════
    // PASO 2: Guardar PRIMERA línea del mapa
    // ═══════════════════════════════════════════════════════════
    // IMPORTANTE: 'first_line' viene con '\n' al final (de GNL)
    // Ejemplo: "1111111\n" → queremos solo "1111111"
	trimmed = ft_strtrim(first_line, "\n");  // Crea copia sin \n
	if (!trimmed)
		return (1);
	temp_map[0] = trimmed;  // Guardamos primera línea
	game->map.height = 1;   // Empezamos contando desde 1
	
	// ═══════════════════════════════════════════════════════════
    // PASO 3: Leer RESTO del mapa con GNL
    // ═══════════════════════════════════════════════════════════
    // ¿Por qué funciona? GNL mantiene un "cursor" interno en el fd
    // Cada llamada lee la SIGUIENTE línea automáticamente:
    //
    // 1ª llamada GNL (en parse_cub_file): lee "1111111\n"
    // 2ª llamada GNL (aquí, bucle while):  lee "1000001\n"
    // 3ª llamada GNL (aquí, bucle while):  lee "1N00001\n"
    // 4ª llamada GNL (aquí, bucle while):  lee "1111111\n"
    // 5ª llamada GNL (aquí, bucle while):  lee "\n" (vacía)
    //
	while ((line = get_next_line(fd)) != NULL)
	{
		// Saltar espacios/tabs para ver si hay contenido real
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		
		  // ───────────────────────────────────────────────────────
        // DETECCIÓN DE FIN DE MAPA
        // ───────────────────────────────────────────────────────
        // Si línea está vacía (solo '\n' o espacios) → FIN del mapa
        // Subject dice: "map must be the last element"
        // Entonces verificamos que NO haya contenido después
        //
		if (line[i] == '\n' || line[i] == '\0')
		{
			free(line);
			// Leer resto del archivo - debe estar vacío
			while ((line = get_next_line(fd)) != NULL)
			{
				i = 0;
				while (line[i] && (line[i] == ' ' || line[i] == '\t'))
					i++;
				// Si encontramos contenido no-vacío → ERROR
				if (line[i] != '\n' && line[i] != '\0')
				{
					free(line);
					print_error("Content found after map (map must be last)");
					return (1);
				}
				free(line);
			}
			break;  // Salimos del loop, ya terminamos con el mapa
		}
		//  AÑADIR: Validar caracteres válidos
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			if (line[j] != '0' && line[j] != '1' && 
				line[j] != 'N' && line[j] != 'S' && 
				line[j] != 'E' && line[j] != 'W' && 
				line[j] != ' ' && line[j] != '\t')
			{
				free(line);
				print_error("Invalid character in map");
				return (1);
			}
			j++;
		}
		
		// ───────────────────────────────────────────────────────
        // GUARDAR LÍNEA DEL MAPA
        // ───────────────────────────────────────────────────────
		trimmed = ft_strtrim(line, "\n");
		free(line);  // Liberamos la línea original de GNL

		if (!trimmed)
			return (1);
		// Guardar línea limpia y aumentar contador (lo tenemos en 1, guarda en 1 y aumenta a 2)	
		temp_map[game->map.height++] = trimmed;
		//mejor como arriba para ganar línea
		// temp_map[game->map.height] = trimmed;
        // game->map.height++;  // Ahora tenemos una línea más

	}
	temp_map[game->map.height] = NULL;  // Marcar final del array
	
	// ═══════════════════════════════════════════════════════════
    // PASO 4: Calcular ancho máximo
    // ═══════════════════════════════════════════════════════════
    // Necesitamos saber la línea más larga (para malloc después)
	game->map.width = 0;
	i = 0;
	while (i < game->map.height)
	{
		if ((int)ft_strlen(temp_map[i]) > game->map.width)
			game->map.width = ft_strlen(temp_map[i]);
		i++;
	}
	// ═══════════════════════════════════════════════════════════
    // PASO 5: Asignar mapa parseado a la estructura del juego
    // ═══════════════════════════════════════════════════════════
	game->map.grid = temp_map;
	printf("\n Mapa: %d líneas, ancho: %d\n", game->map.height, game->map.width);
	
	return (0);
}

/*
** find_player - Busca la posición del jugador en el mapa (N/S/E/W)
**
** Recorre el mapa buscando N, S, E o W y guarda la posición y dirección.
**
** @game: Estructura con el mapa ya parseado
** Return: 0 si OK, 1 si no se encontró jugador o hay más de uno
*/
int	find_player(t_game *game)
{
	int		y;
	int		x;
	int		found;
	char	c;

	y = 0;
	found = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (found)  // Ya encontramos un jugador antes
				{
					print_error("Multiple player positions found");
					return (1);
				}
				game->map.player_x = x;
				game->map.player_y = y;
				game->map.start_dir = c;
				found = 1;
			}
			x++;
		}
		y++;
	}
	if (!found)
	{
		print_error("No player position (N/S/E/W) found in map");
		return (1);
	}
	
	printf(" Jugador encontrado en: (%d, %d) dirección '%c'\n", 
		game->map.player_x, game->map.player_y, game->map.start_dir);
	
	return (0);
}