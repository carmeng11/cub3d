#include "cub3d.h"
#include <stdlib.h>
//LUEGO CREAR FICHERO init.c quizá
// static void	data_init(t_game *game)
// {
// 	game->map.width = 10;
// 	game->map.height = 10;
// 	//fractal->shift_x = 0.0;
// 	//fractal->shift_y = 0.0;
// 	//fractal->zoom = 1.0;
// 	//fractal->colorchange = 0;
// }
//MIRAR SI SE METE LA FUNCION EN FICHERO INIT:C


void	map_draw(t_game *game)
{
	// Dibujar un cuadrado rojo de prueba
	// draw_square(&game->img, 100, 100, 50, 0xFF0000);  // Rojo
	// draw_square(&game->img, 200, 100, 50, 0x00FF00);  // Verde
	// draw_square(&game->img, 300, 100, 50, 0x0000FF);  // Azul
	//Inicializar mapa de prueba
	init_map(game);
	// Dibujar el minimap
	draw_minimap(game);
	// //Finalmente, después de haber recorrido todos los píxeles de la ventana,y dibujar el map la función mlx_put_image_to_window 
	// //se llama para renderizar la imagen en la ventana.
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	//Parámetros (conexión a la librería gráfica (MiniLibX), ventana en la que se mostrará la imagen, puntero a la imagen que contine los píxeles,
	// coordenadas de la ventana donde se coloca la imagen. en este caso esquina superior izda)
	
}

// Función para crear un mapa de prueba simple
void	init_map(t_game *game)
{
	int i;
	int	j;
	
	// Definir tamaño del mapa
	// game->map.width = 10;
	// game->map.height = 10;
	
	// Reservar memoria para la matriz. Para 5 filas → reservas 5 punteros
	// Un array de punteros. Para un mapa de altura 5, memoria para 5 punteros, esto sería 5 * 8
	game->map.grid = malloc(sizeof(int *) * game->map.height);
	i = 0;
	while (i < game->map.height)
	{
		//Segunda reserva (cada fila como array)
		//Para ancho 7 → reservas 7 enteros
		//Total por fila: 7 × 4 = 28 bytes
		game->map.grid[i] = malloc(sizeof(int) * game->map.width);
		i++;
		//en resumen se reserva memoria para cada fila entendiéndolo como un array". 
		//Cada fila es un array separado en memoria, y el array de punteros solo guarda las direcciones de dónde empieza cada fila.
	}
	i = 0;
	
	// Crear un mapa simple: bordes con paredes (1) y centro vacío (0)
	// Fila 0: 1 1 1 1 1 1 1 1 1 1
	// game->map.grid[0][0] = 1; game->map.grid[0][1] = 1; game->map.grid[0][2] = 1;
	// game->map.grid[0][3] = 1; game->map.grid[0][4] = 1; game->map.grid[0][5] = 1;
	// game->map.grid[0][6] = 1; game->map.grid[0][7] = 1; game->map.grid[0][8] = 1;
	// game->map.grid[0][9] = 1;
	while (i < game->map.width)
	{
		game->map.grid[0][i] = 1;
		i++;
	}
	
	// Filas 1-8: paredes en los bordes
	i = 1;
	// while (i < 9)
	// {
	// 	game->map.grid[i][0] = 1;  // Pared izquierda
	// 	game->map.grid[i][1] = 0;
	// 	game->map.grid[i][2] = 0;
	// 	game->map.grid[i][3] = 0;
	// 	game->map.grid[i][4] = 0;
	// 	game->map.grid[i][5] = 0;
	// 	game->map.grid[i][6] = 0;
	// 	game->map.grid[i][7] = 0;
	// 	game->map.grid[i][8] = 0;
	// 	game->map.grid[i][9] = 1;  // Pared derecha
	// 	i++;
	// }
	while (i < (game->map.height - 1))
	{
		j = 1;
		game->map.grid[i][0] = 1; // Pared izquierda
		while (j < (game->map.width - 1))
		{
			game->map.grid[i][j] = 0;
			j++;
		}
		game->map.grid[i][game->map.width - 1] = 1;  // Pared derecha
		i++;
	}
	
	// Fila 9: 1 1 1 1 1 1 1 1 1 1
	// game->map.grid[9][0] = 1; game->map.grid[9][1] = 1; game->map.grid[9][2] = 1;
	// game->map.grid[9][3] = 1; game->map.grid[9][4] = 1; game->map.grid[9][5] = 1;
	// game->map.grid[9][6] = 1; game->map.grid[9][7] = 1; game->map.grid[9][8] = 1;
	// game->map.grid[9][9] = 1;
	i = 0;
	while (i < game->map.width)
	{
		game->map.grid[game->map.height - 1][i] = 1;
		i++;
	}
	
	// Posición inicial del jugador (centro del mapa)
	game->map.posX = 5;
	game->map.posY = 5;
	game->map.start_dir = 'N';
}
void    draw_minimap(t_game *game)
{
	int tile_size;
	int	y;
	int	x;
	int color;
	int px;
	int py;
	
	tile_size = 20; // Tamaño de cada celda
	y = 0;
	while (y < game->map.height)
    {
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 1)
				color = 0xFFFFFF; // Blanco para paredes
			else
				color = 0x000000; // Negro para espacios
			draw_square(&game->img, x * tile_size, y * tile_size,
						tile_size, color);
			x++;
			}
		y++;
	}
    
    // Dibuja jugador (punto rojo)
    px = game->map.posX * tile_size;
    py = game->map.posY * tile_size;
    draw_square(&game->img, px - 3, py - 3, 6, 0xFF0000);
}

void    draw_square(t_img *img, int x, int y, int size, int color)
{
    int	i;
	int	j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
        
}
