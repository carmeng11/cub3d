#include "cub3d.h"
#include <string.h>
#include <stdlib.h>

// Función para parsear una línea de textura (NO, SO, WE, EA)
// Formato esperado: "NO ./textures/north.xpm"
int	parse_texture_line(char *line, char **texture)
{
	char	*path;
	int		i;

	// Saltar espacios después del identificador (NO, SO, etc.)
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;

	// Si ya no hay nada, error
	if (!line[i])
	{
		print_error("Missing texture path");
		return (1);
	}

	// Guardar la ruta (eliminar salto de línea si existe)
	path = strdup(&line[i]);
	if (!path)
	{
		print_error("Memory allocation failed");
		return (1);
	}

	// Eliminar \n al final si existe
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';

	// Si ya había una textura asignada, error (duplicado)
	if (*texture != NULL)
	{
		free(path);
		print_error("Duplicate texture identifier");
		return (1);
	}

	*texture = path;
	return (0);
}
