#include "cub3d.h"
#include <stdlib.h>

//QUIZA RENOMBRAR EL FICHERO A RENDER

void	map_draw(t_game *game)
{
	// Dibujar un cuadrado rojo de prueba
	// draw_square(&game->img, 100, 100, 20, 0xFF0000);  // Rojo
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
	
	// Definir tamaño del mapa lo definimos en la función data_init
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
	// ej 10 x 10
	// Fila 0: 1 1 1 1 1 1 1 1 1 1
	// Fila 9: 1 1 1 1 1 1 1 1 1 1
	while (i < game->map.width)
	{
		game->map.grid[0][i] = 1; //fila 0
		game->map.grid[game->map.height - 1][i] = 1; //fila 9
		i++;
	}
	// Filas intermedias paredes en los bordes
	// 1 0 0 0 0 0 0 0 0 1
	i = 1;//empieza en 1 pq la fila 1 ya se ha creado
	while (i < (game->map.height - 1))
	{
		j = 1;
		game->map.grid[i][0] = 1; // Pared izquierda la y va variando y la x es 0
		while (j < (game->map.width - 1))
		{
			game->map.grid[i][j] = 0;
			j++;
		}
		game->map.grid[i][game->map.width - 1] = 1;  // Pared derecha la y va variando y la x es la última celda de la fila
		i++;
	}
	// Posición inicial del jugador (centro del mapa)
	//LO TENEMOS DEFINIDO EN INIT.C
	// game->map.posX = game->map.width / 2;
	// game->map.posY = game->map.height / 2;
    // game->map.start_dir = 'N'; // Dirección inicial
}
// DIBUJA TODOS LOS CUADRADOS DEL MAPA
// Dibuja todo el minimap (10×10 celdas, cada celda es un cuadrado de 20×20 píxeles)
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
	while (y < game->map.height)  // Recorre filas del MAPA (ej 10 filas)
    {
		x = 0;
		while (x < game->map.width) // Recorre columnas del MAPA (10 columnas)
		{
			if (game->map.grid[y][x] == 1)
				color = 0xFFFFFF; // Blanco para paredes
			else
				color = 0x000000; // Negro para espacios
			// Dibuja un CUADRADO de 20×20 píxeles por cada celda del mapa
			draw_square(&game->img, x * tile_size, y * tile_size,
						tile_size, color);
			x++;
		}
		y++;
	}
    
    // Dibuja jugador (punto rojo)
    // px = game->map.posX * tile_size;  // Esquina superior izq de la celda
    // py = game->map.posY * tile_size;
    // Centrar: (tile_size - tamaño_jugador) / 2 = (20 - 10) / 2 = 5
	px = (int)game->player.x;  // ← Cambiar de game->map.posX
    py = (int)game->player.y;  // ← Cambiar de game->map.posY
    draw_square(&game->img, px, py, 10, 0x00FF00);

}

// void	draw_minimap(t_game *game)
// {
// 	int		y;
// 	int		x;
// 	int		color;

// 	color = 0xFF0000;
// 	y = 0;
// 	while (game->map.grid[y] != NULL)//recorremos las filas hasta el último puntero nulo de cuando se hizo el malloc con tantos punteros como n de filas más uno
// 	//while (map[y])
// 	{
// 		x = 0;
// 		//while (map[x] != NULL) //recorremos las columnas esto no estaría correcto 
// 		while (game->map.grid[y][x] != '\0') //recorremos cada una de las filas hasta el carácter nulo del final
// 		{
// 			if (game->map.grid[y][x] == '1')
// 				draw_square(&game->img, x * BLOCK, y * BLOCK, BLOCK, color);
// 				//si quiero que el mapa no esté exactamente en 0,0 sumaría a
// 				//x * BLOCK, y * BLOCK  10, 20, etc...
// 				//x * BLOCK + 20, y * BLOCK + 20
// 			x++;
// 		}
// 		y++;
// 	}
// }
//DIBUJA UN CUADRADO muchos pixeles
//DIBUJA UN CUADRADO RELLENO de size × size píxeles empezando en (x, y)
void    draw_square(t_img *img, int x, int y, int size, int color)
{
    int	i;
	int	j;
	
	i = 0;
	while (i < size) // Recorre filas del cuadrado
	{
		j = 0;
		while (j < size) // Recorre columnas del cuadrado
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			//dibuja un pixel en la posición exacta (x, y)
			j++;
		}
		i++;
	}
        
}

//PINTAMOS CAUADRADO SIN RELLENO, SOLO BORDES
// void	draw_square(t_img *img, t_map *map, int size)
// {
// 	//pintamos la línea superior
// 	int	i;
// 	i = 0;
// 	while (i < size)
// 	{
// 		put_pixel(map->posX + i, map->posY, map->color);//pintamos la línea horizontal primera
// 		put_pixel(map->posX+ i, map->posY + size, map->color);//pintamos la línea horizontal segunda
// 		put_pixel(map->posX, map->posY + i, map->color);//pintamos la línea vertical izda
// 		put_pixel(map->posX + size, map->posY + i, color);//pintamos la línea vertical dcha
// 		i++;
// 	}
// }

// void	draw_square(t_img *img, int x, int y, int size, int color)
// {
// 	//pintamos la línea superior
// 	int	i;
// 	i = 0;
// 	while (i < size)
// 	{
// 		my_mlx_pixel_put(img, x + i, y, color);//pintamos la línea horizontal primera
// 		my_mlx_pixel_put(img, x + i, y + size, color);//pintamos la línea horizontal segunda
// 		my_mlx_pixel_put(img, x, y + i, color);//pintamos la línea vertical izda
// 		my_mlx_pixel_put(img, x + size, y + i, color);//pintamos la línea vertical dcha
// 		i++;
// 	}
// }


