#include "cub3d.h"
#include <stdlib.h>

// Función auxiliar para convertir string a int y validar rango
static int	ft_atoi_rgb(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	
	// Saltar espacios
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	
	// Convertir dígitos
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	// Validar rango (0-255)
	if (result < 0 || result > 255)
		return (-1);
	
	return (result);
}

// Función auxiliar para liberar el array de ft_split
static void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
** parse_color_line - Parsea una línea de color (F o C)
** 
** Formato esperado: "F 220,100,0" o "C 225,30,0"
** Usa ft_split para separar por comas los valores R,G,B
**
** @line: Línea después del identificador (ej: " 220,100,0")
** @color: Puntero a la estructura donde guardar RGB
**
** Return: 0 si OK, 1 si error
*/
int	parse_color_line(char *line, t_color *color)
{
	char	**rgb;
	int		i;

	// Saltar espacios después del identificador (F o C)
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;

	// Separar por comas usando ft_split (permitida en 42)
	rgb = ft_split(&line[i], ',');
	if (!rgb)
	{
		print_error("Memory allocation failed");
		return (1);
	}

	// Verificar que tengamos exactamente 3 valores (R, G, B)
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		free_split(rgb);
		print_error("Invalid color format (need R,G,B)");
		return (1);
	}

	// Convertir y validar cada componente (0-255)
	color->r = ft_atoi_rgb(rgb[0]);
	color->g = ft_atoi_rgb(rgb[1]);
	color->b = ft_atoi_rgb(rgb[2]);

	// Liberar memoria del split
	free_split(rgb);

	// Validar que todos los valores estén en rango
	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		print_error("Color values must be 0-255");
		return (1);
	}

	return (0);
}
