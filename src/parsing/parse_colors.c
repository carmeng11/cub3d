#include "cub3d.h"
#include <stdlib.h>
#include <string.h>

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

// Función para parsear una línea de color (F o C)
// Formato esperado: "F 220,100,0"
int	parse_color_line(char *line, t_color *color)
{
	char	*rgb[3];
	int		i;
	int		j;
	char	*token;

	// Saltar espacios después del identificador (F o C)
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;

	// Separar por comas (usar strtok o implementar tu propio split)
	// Versión simple con strtok:
	token = strtok(&line[i], ",");
	j = 0;
	while (token && j < 3)
	{
		rgb[j] = token;
		token = strtok(NULL, ",");
		j++;
	}

	// Verificar que tengamos exactamente 3 valores
	if (j != 3)
	{
		print_error("Invalid color format (need R,G,B)");
		return (1);
	}

	// Convertir y validar cada componente
	color->r = ft_atoi_rgb(rgb[0]);
	color->g = ft_atoi_rgb(rgb[1]);
	color->b = ft_atoi_rgb(rgb[2]);

	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		print_error("Color values must be 0-255");
		return (1);
	}

	return (0);
}
