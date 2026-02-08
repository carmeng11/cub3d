#include "cub3d.h"

//QUIZA METER EN RENDER

// Función para escribir un píxel en la imagen
void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    // Calcular la posición del píxel en memoria
    dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	// Escribir el color en esa posición
    *(unsigned int*)dst = color;
}