#include "cub3d.h"

// Función para escribir un píxel en la imagen
// void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
//     char    *dst;

//     // Calcular la posición del píxel en memoria
//     dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
// 	// Escribir el color en esa posición
//     *(unsigned int*)dst = color;
// }

//INCORPORAMOS RENDER_GAME
int render_game(t_game *game)
{
    // static int frame = 0;
    // printf("Frame: %d\n", frame++); 
    move_player(game);

    clear_image(game);
	// Dibujar el minimap actualizado
	draw_minimap(game);
  	
	// Mostrar la imagen en la ventana
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}
void clear_image(t_game *game)
{
    int y;  // Contador de filas
    int x;  // Contador de columnas

    // Recorrer TODA la pantalla (cada píxel)
    y = 0;
    while (y < HEIGHT)  // Para cada fila (de 0 a 719)
    {
        x = 0;
        while (x < WIDTH)  // Para cada columna (de 0 a 1279)
        {
            // Poner el píxel en negro (0x000000)
            // Esto "borra" lo que había antes,lo pone a negro
            my_mlx_pixel_put(&game->img, x, y, 0x000000);
            x++;
        }
        y++;
    }
}

//FUNCION PARA OPTIMIZAR CLEAR IMAGE

// void clear_image(t_game *game)
// {
//     ft_memset(game->img.pixels_ptr, 0, WIDTH * HEIGHT * 4);
// }