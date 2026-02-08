#include "cub3d.h"


int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*extension;
	size_t	len;

	(void)game;  // TODO: usar game cuando parsees
	
	//En la práctica, NO es necesario porque argv[1] nunca será NULL. 
	//Pero es una programación defensiva por si alguien llama a 
	//parse_cub_file(NULL, &game) por error. Se puede eliminar la comprobación
	// if (!filename)
	// {
	// 	print_error("Invalid filename");
	// 	return (1);
	// }
	//VERIFICAR .CUB
	// 1. VAMOS AL FINAL DEL FICHERO Y COMPARAMOS CARACTER A CARACTER
	//compara caracter a caracter empezanod por el final
	// len = 0;
	// while (filename[len])
	// 	len++;
	
	// if (len < 5 || filename[len - 4] != '.' || filename[len - 3] != 'c' || 
	// 	filename[len - 2] != 'u' || filename[len - 1] != 'b')
	// {
	// 	print_error("File must have .cub extension");
	// 	return (1);
	// }
	//2. OBTENEMOS STRLEN Y RECORREMOS EL FINAL DE LA CADENA HASTA ENCONTRAR EL .
	//SACAMOS LA CADENA Y COMPARAMOS CON LA FUNCION FT_STRCNMP

	// len = ft_strlen(filename);// map.cub len = 7
	// extension = NULL;
	// while (len > 0)
	// {
	// 	len--; //Decrementar primero para no leer el \0
	// 	if (filename[len] == '.')
	// 	{
	// 		extension = &filename[len];
	// 		break; //saliar al encontrar el .
	// 	}
	// 	len--;
	// }
	// if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	// {
	// 	print_error("File must have .cub exxxxtension");
	// 	return (1);
	// }
	//3. CON FT_STRRCHR Y STRNCMP
	extension = ft_strrchr(filename, '.');//sacamos la cadena cuando encuentra el caracter pero desde el final
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("File must have .cub extension");
		return (1);
	}

	// Abrir archivo
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (1);
	}

	// TODO: Parsear línea por línea
	// TODO: Identificar texturas (NO, SO, WE, EA)
	// TODO: Identificar colores (F, C)
	// TODO: Leer mapa

	close(fd);
	return (0);
}
