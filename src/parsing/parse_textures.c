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
	path =ft_strdup(&line[i]);
	if (!path)
	{
		print_error("Memory allocation failed");
		return (1);
	}

	// Eliminar \n al final si existe
	// GNL devuelve la línea CON el \n, hay que quitarlo
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';  // Reemplaza \n por \0 (fin de string)

	// VERIFICACIÓN: Si ya había una textura asignada, error (duplicado)
	// *texture desreferencia el puntero para ver si ya apunta a algo
	// Ejemplo: si NO ya se parseó antes, *texture != NULL
	if (*texture != NULL)
	{
		free(path);  // Liberar la memoria que acabamos de asignar
		print_error("Duplicate texture identifier");
		return (1);
	}

	// ASIGNACIÓN: Modificar el puntero original para que apunte al path
	// *texture = desreferencia el doble puntero para modificar el puntero original
	// Esto hace que game->textures.north (por ejemplo) apunte a "path"
	*texture = path;
	return (0);
}
