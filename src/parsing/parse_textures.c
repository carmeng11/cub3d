#include "cub3d.h"

/*
** extract_path - Extrae el path de textura desde la línea
**
** @line: Línea a parsear
** @path: Puntero donde guardar el path extraído
** Return: 0 si OK, 1 si error
*/
static int	extract_path(char *line, char **path)
{
	int	i;
	int	len;

	i = 0;
	// Recibe la línea después del identificador,
		//por ejemplo " ./textures/north.xpm\n".
	// Salta espacios y tabs iniciales con i
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	len = 0;
	while (line[i + len] && line[i + len] != '\n' && line[i + len] != ' ')
		len++;
	if (len == 0)
	{
		print_error("Empty texture path");
		return (1);
	}
	// saltar espacios finales y si encuentra algo que de error gestiona como error este caso EA ./textures/east.xpm     fgfgfg
	// while (line[i + len] && (line[i + len] == ' ' || line[i + len] == '\t'))
	//     len++;
	// // si queda algo que no sea \n o \0 → error
	// if (line[i + len] != '\n' && line[i + len] != '\0')
	// {
	//     print_error("Invalid texture pathhhhh");
	//     return (1);
	// }
	*path = ft_substr(line, i, len);
	if (!*path)
	{
		return (1);
	}
	return (0);
}

/*
** validate_texture_file - Verifica que el archivo existe y es .xpm
**
** @path: Ruta del archivo a verificar
** Return: 0 si OK, 1 si error
*/
static int	validate_texture_file(char *path)
{
	int		fd;
	size_t	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Texture file not found: %s\n", path);
		return (1);
	}
	close(fd);
	// verificamos que es .xpm En la ruta "NO ./textures/north.xpm" (path + len
		//- 4) nos situa justo delante del '.'
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error: Texture must be .xpm: %s\n", path);
		return (1);
	}
	return (0);
}

/*
** parse_texture_line - Parsea una línea de textura del .cub
**
** @line: Línea del archivo .cub
** @texture_path: Puntero al campo de textura
** Return: 0 si OK, 1 si error
*/
int	parse_texture_line(char *line, char **texture_path)
{
	char *path;

	if (extract_path(line, &path) != 0)
		return (1);
	if (validate_texture_file(path))
	{
		free(path);
		return (1);
	}
	if (*texture_path != NULL)
	{
		free(path);
		print_error("Duplicate texture identifier");
		return (1);
	}
	*texture_path = path;
	printf("✓ Texture path validated: %s\n", path);
	return (0);
}