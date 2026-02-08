#include "cub3d.h"
#include <stdlib.h>

// QUIZA RENOMBRAR EL FICHERO A RENDER

void	map_draw(t_game *game)
{
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}

// FUNCION CON TILE_SIZE QUE ME DABA PROBLEMAS AL TEBER BLOCK Y ILE_SIZE
// void	init_map(t_map *map)
// {
// 	map->width = 30;
// 	map->height = 20;
// }
// DIBUJA TODOS LOS CUADRADOS DEL MAPA
// Dibuja todo el minimap (10×10 celdas,
	//cada celda es un cuadrado de 20×20 píxeles)
// void    draw_minimap(t_game *game)
// {
// 	int tile_size;
// 	int	y;
// 	int	x;
// 	int color;
// 	int px;
// 	int py;

// 	tile_size = 20; // Tamaño de cada celda
// 	y = 0;
// 	while (y < game->map.height)  // Recorre filas del MAPA (ej 10 filas)
//     {
// 		x = 0;
// 		while (x < game->map.width) // Recorre columnas del MAPA (10 columnas)
// 		{
// 			if (game->map.grid[y][x] == 1)
// 				color = 0xFFFFFF; // Blanco para paredes
// 			else
// 				color = 0x000000; // Negro para espacios
// 			// Dibuja un CUADRADO de 20×20 píxeles por cada celda del mapa
// 			draw_square(&game->img, x * tile_size, y * tile_size,
// 						tile_size, color);
// 			x++;
// 		}
// 		y++;
// 	}

//     // Dibuja jugador (punto rojo)
//     // px = game->map.posX * tile_size;  // Esquina superior izq de la celda
//     // py = game->map.posY * tile_size;
//     // Centrar: (tile_size - tamaño_jugador) / 2 = (20 - 10) / 2 = 5
// 	px = (int)game->player.x;  // ← Cambiar de game->map.posX
//     py = (int)game->player.y;  // ← Cambiar de game->map.posY
//     draw_square(&game->img, px, py, 10, 0x00FF00);

// }


void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (game->map.grid[y] != NULL)
	{
		x = 0;
		while (game->map.grid[y][x] != '\0')
		{
			if (game->map.grid[y][x] == '1')
				color = 0x0000FF; // Blanco = pared
			else
				color = 0x000000; // Negro = espacio
			draw_square(&game->img, x * BLOCK, y * BLOCK, BLOCK, color);
			x++;
		}
		y++;
	}
	// Jugador
	draw_square(&game->img, (int)game->player.x - 5, (int)game->player.y - 5,
		10, 0x00FF00);
}
// DIBUJA UN CUADRADO muchos pixeles
// DIBUJA UN CUADRADO RELLENO de size × size píxeles empezando en (x, y)
// void	draw_square(t_img *img, int x, int y, int size, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < size) // Recorre filas del cuadrado
// 	{
// 		j = 0;
// 		while (j < size) // Recorre columnas del cuadrado
// 		{
// 			my_mlx_pixel_put(img, x + j, y + i, color);
// 			// dibuja un pixel en la posición exacta (x, y)
// 			j++;
// 		}
// 		i++;
// 	}
// }

// PINTAMOS CAUADRADO SIN RELLENO, SOLO BORDES

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	//pintamos la línea superior
	int	i;
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(img, x + i, y,	color);//pintamos la línea horizontal primera
		my_mlx_pixel_put(img, x + i, y + size - 1, color);//pintamos la línea horizontal segunda
		my_mlx_pixel_put(img, x, y + i, color);//pintamos la línea vertical izda
		my_mlx_pixel_put(img, x + size -1, y + i, color);//pintamos la línea vertical dcha
		i++;
	}
}
