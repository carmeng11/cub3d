
#include "cub3d.h"


int main(int argc, char **argv)
{
	t_game	game;
	(void)argv;

	// Verificar argumentos
	if (argc != 2)
	{
		//print_error("Usage_print: ./cub3d <map.cub>");
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", STDERR_FILENO);
		return (1);
	}

	// Parsear archivo .cub y abrir y leer fichero con gnl
	if (parse_cub_file(argv[1], &game) != 0)
		return (1);

	// Inicializar juego
	game.name = "Cub3D";
	game_init(&game);
	
	return (0);
}




