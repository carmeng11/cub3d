
#include "cub3d.h"

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}
void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

//futuro
//void game_destroy(t_game *game)
// {
//     // Liberar memoria del mapa
//     // Destruir imagen, ventana, mlx
//     // Útil para cuando implementes el parsing del archivo .cub
// }

// int game_destroy(t_game *game)
// {
// 	mlx_destroy_image(game->mlx,
// 		game->data);
// 	mlx_destroy_window(game->mlx,
// 		game->win);
// 	mlx_destroy_display(game->mlx);
// 	free(game->mlx);
// 	exit(EXIT_SUCCESS);
// }


// void	data_init(t_game *game)
// {
// 	game->map.width = 30;
// 	game->map.height = 20;
// 	// game->map.pos_x = 5.0;      // Posición inicial del jugador
//     // game->map.pos_y = 5.0;
// 	game->map.pos_x = game->map.width / 2;
// 	game->map.pos_y = game->map.height / 2;
//     game->map.start_dir = 'N'; // Dirección inicial
//     // En el futuro: texturas, colores, etc.

// }


char	**get_map(void)
{
	char **map = malloc(sizeof(char*) * 11);

	map[0] = "11111111111111111111"; //map[y]
	map[1] = "10000000000000000001"; //map[y + 1]
	map[2] = "10000000000000000001";
	map[3] = "10000000100000000001";
	map[4] = "10000000000000000001";
	map[5] = "10000010000000000001";
	map[6] = "10000000100000000001";
	map[7] = "10000000000000000001";
	map[8] = "10000000000000000001";
	map[9] = "11111111111111111111";
	map[10] = NULL;
	return (map);
}

void	init_map(t_map *map)
{
	map->width = 30;
	map->height = 20;
}
// char **get_map(void)
// {
// t_map *map;
// int i;
// int j;

// map = malloc(sizeof(t_map));
// if (!map)
// 	malloc_error();
// init_map(map);
// map->grid = malloc(sizeof(char *) * (map->height + 1));
// if (!map->grid)
// 	malloc_error();
// i = 0;
// while (i < map->height)
// {
// 	map->grid[i] = malloc(sizeof(char) * (map->width + 1));
// 	if (!map->grid[i])
// 		malloc_error();
// 	j = 0;	
// 	while (j < map->width)
// 	{
// 			map->grid[i][j] = '0';
// 			j++;
// 	}
// 	map->grid[i][map->width] = '\0';
// 	i++;
// }
// map->grid[map->height] = NULL;
// //rellenamos las columnas primera y ultima de 1
// i = 0;
// while (i < map->height)
// {
// 	map->grid[i][0] = '1';
// 	map->grid[i][map->width - 1] = '1';
// 	i++;
// }
// //rellenamos las filas superior e inferior
// j = 0;
// while (j < map->width)
// {
// 	map->grid[0][j] = '1';
// 	map->grid[map->height - 1][j] = '1';
// 	j++;
// }
// return (map->grid);
// }



// char	**get_map(t_map *map)
// {
// 	char	**mall;
// 	int		i;
// 	int		j;
	
// 	// map->width = 20;
// 	// map->height = 20;
// 	init_map(map);
// 	mall = malloc(sizeof(char *) * (map->height + 1)); //RESERVAMOS MEMORIA PARA TANTOS PUNTEROS COMO FILAS
// 	i = 0;
// 	while (i < map->height) //i recorre las filas iteramos de arriba a abajo
// 	{
// 		mall[i] = malloc(sizeof(char) * (map->width + 1));//RESERVAMOS MEMORIA PARA EL STRING DE CADA UNA DE LAS FILAS MAS EL CARATER NULO DEL FINAL
// 		j = 0;
// 		// Inicializar toda la fila con '0' (espacios vacíos)
// 		while (j < map->width) //j recorre las columnas, iteramos toda la lonfitud de la fila
// 		{
// 			mall[i][j] = '0';
// 			j++;
// 		}
// 		mall[i][map->width] = '\0';  // ← ¡IMPORTANTE! Terminar la string
// 		i++;
// 	}
// 	mall[map->height] = NULL;//el último puntero de la última fila es nulo
// 	// Ahora dibujar las paredes (bordes del mapa)
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		// Pared izquierda y derecha
// 		mall[i][0] = '1';
// 		mall[i][map->width - 1] = '1';
// 		i++;
// 	}
	
// 	// Pared superior e inferior
// 	j = 0;
// 	while (j < map->width)
// 	{
// 		mall[0][j] = '1';
// 		mall[map->height - 1][j] = '1';
// 		j++;
// 	}
	
// 	return (mall);
// }



void	game_init(t_game *game)
{
	// t_map map;
	// map.grid = NULL;
	
	init_player(&game->player);//inicializamos el jugador
	//game->map = get_map(&map); //creamos el mapa con 0 1
	game->map = get_map();

	game->mlx = mlx_init();//Se inicia la conexión a la librería mlx
	if (game->mlx == NULL)//Si no se puede inicializar, se llama a malloc_error() para gestionar el error.
		malloc_error();
	//ventana con un tamaño de WIDTH x HEIGHT y se le asigna un título
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, game->name);
	//si la ventana no se construye correctamente se destruye la conexión y se llama a malloc error
	if (game->win == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	//Se crea una nueva imagen en la memoria para renderizar luego el raycasting
	game->img = mlx_new_image(game->mlx,
		WIDTH, HEIGHT);
	//Si no se puede crear la imagen, se destruyen la ventana y la conexión, y se llama a malloc_error()
	if (game->img == NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	//Esta línea obtiene la dirección de memoria 
	//donde está el array de píxeles de la imagen.
	game->data = mlx_get_data_addr(game->img,
			&game->bpp,//se obtienen los bytes por pixel
			&game->line_len,//la longitud de línea de la imagen
			&game->endian);//y el orden de los bytes 
	
	// Test: dibujar cuadrados de colores
	// data_init(game);
	// map_draw(game);
	//mirar si se crea una función events_init que llame a todas las mlx_hook
	// events_init(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	//mlx_loop(game->mlx);
}