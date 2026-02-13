
#include "cub3d.h"

//futuro
//void game_destroy(t_game *game)
// {
//     // Liberar memoria del mapa
//     // Destruir imagen, ventana, mlx
//     // Útil para cuando implementes el parsing del archivo .cub
// }

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}
//MEJOR HACERLO COMO ESTÁ DEBAJO
// static float	get_start_angle(t_game	*game)
// {
// 	t_map	*m;

// 	m = &game->map;
// 	if (m->start_dir == 'N')
// 		return (PI / 2);		// 90° - Norte (arriba)
// 	else if (m->start_dir == 'S')
// 		return (3 * PI / 2);	// 270° - Sur (abajo)
// 	else if (m->start_dir == 'W')
// 		return (PI);			// 180° - Oeste (izquierda)
// 	else if (m->start_dir == 'E')
// 		return (0);				// 0° - Este (derecha)
// 	return (PI / 2);			// Default: Norte
// }
static float get_start_angle(char dir)  // ← Pasar solo el char
{
    if (dir == 'N')
        return (PI / 2);
    else if (dir == 'S')
        return (3 * PI / 2);
    else if (dir == 'W')
        return (PI);
    else if (dir == 'E')
        return (0);
    return (PI / 2);
}

void	init_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->x = game->map.posX * BLOCK;
	//p->x = WIDTH / 2;
	p->y = game->map.posY * BLOCK;
	//p->y = HEIGHT / 2; 
	//p->angle = PI / 2;
	p->angle = get_start_angle(game->map.start_dir);  // N, S, E, W
	p->key_up = false;
	p->key_down = false;
	p->key_left = false;
	p->key_right = false;
	p->left_rotate = false;
	p->right_rotate = false;

}

// Función de test para probar el dibujo de píxeles

// void	data_init(t_game *game)
// {
// 	//int	tile_size = 10;
// 	game->map.width = 20;
// 	game->map.height = 20;
// 	game->map.posX = 5.0;      // Posición inicial del jugador
//     game->map.posY = 5.0;
// 	// game->map.posX = game->map.width / 2;
// 	// game->map.posY = game->map.height / 2;
//     game->map.start_dir = 'N'; // Dirección inicial
//     // En el futuro: texturas, colores, etc.
// 	// Ya NO inicializas nada aquí
//     // Todo se hará en init_map()
    
//     // Solo inicializar punteros a NULL (seguridad)
//     //game->map.grid = NULL;

// }

// Función para crear un mapa de prueba simple
void init_map(t_game *game)
{

	char **map;
    
    // Crear mapa simple
    map = malloc(sizeof(char*) * 11);
    
    map[0] = "11111111111111111111";
    map[1] = "10000000000000000001";
    map[2] = "10000000000000000001";
    map[3] = "10000000100000000001";
    map[4] = "10000000000000000001";  // ← SIN 'N', solo '0' y '1'
    map[5] = "10000010000000000001";
    map[6] = "10000000100000000001";
    map[7] = "10000000000000000001";
    map[8] = "10000000000000000001";
    map[9] = "11111111111111111111";
    map[10] = NULL;
    
    // Asignar mapa
    game->map.grid = map;
    game->map.width = 20;
    game->map.height = 10;
    
    // Posición HARDCODED (centro del mapa)
    game->map.posX = game->map.width / 2;  // Columna 
    game->map.posY = game->map.height / 2;   // Fila 
    game->map.start_dir = 'N';  // Norte
}

void	game_init(t_game *game)
{
	//data_init(game);
	init_map(game);
	init_player(game);
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
	game->img.img_ptr = mlx_new_image(game->mlx,
		WIDTH, HEIGHT);
	//Si no se puede crear la imagen, se destruyen la ventana y la conexión, y se llama a malloc_error()
	if (game->img.img_ptr == NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	//Esta línea obtiene la dirección de memoria 
	//donde está el array de píxeles de la imagen.
	game->img.pixels_ptr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp,//se obtienen los bytes por pixel
			&game->img.line_len,//la longitud de línea de la imagen
			&game->img.endian);//y el orden de los bytes 
	
	// Test: dibujar cuadrados de colores
	//data_init(game);
	//map_draw(game);
	//mirar si se crea una función events_init que llame a todas las mlx_hook
	events_init(game);
	mlx_loop(game->mlx);
}