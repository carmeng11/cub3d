#include "cub3d.h"

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

// int key_hook(int keycode, t_data *data)
// {
//     if (keycode == 65307) // ESC
//     {
//         mlx_destroy_window(data->mlx, data->win);
//         exit(0);
//     }
//     if (keycode == 119) // W
//         printf("Adelante\n");
//     if (keycode == 115) // S
//         printf("Atrás\n");
//     if (keycode == 97)  // A
//         printf("Izquierda\n");
//     if (keycode == 100) // D
//         printf("Derecha\n");
//     return (0);
// }


// Según el subject de Cub3D:
// XK_Up / XK_Down: avanzar/retroceder
// XK_Left / XK_Right: rotar la cámara izquierda/derecha
// XK_Escape: cerrar la ventana

void	events_init(t_game *game)
{
	// Evento de teclado
    mlx_hook(game->win, KeyPress, KeyPressMask, key_hook, game);
    // Evento de cerrar ventana (X roja)
    mlx_hook(game->win, DestroyNotify, StructureNotifyMask, close_window, game);
    // Futuro: mlx_hook para ratón, redibujado, etc.
}

int key_hook(int keycode, t_game *game)
{
    printf("Tecla presionada: %d\n", keycode); // Para ver códigos
    
    if (keycode == XK_Escape)    // ESC
        close_window(game);
    if (keycode == XK_Up)        // Flecha arriba - avanzar
        printf("Avanzar\n");
    if (keycode == XK_Down)      // Flecha abajo - retroceder
        printf("Retroceder\n");
    if (keycode == XK_Left)      // Flecha izquierda - rotar izq
        printf("Rotar izquierda\n");
    if (keycode == XK_Right)     // Flecha derecha - rotar der
        printf("Rotar derecha\n");
    
    return (0);
}

// int main(void)
// {
//     t_data  data;

//     data.mlx = mlx_init();
//     data.win = mlx_new_window(data.mlx, 800, 600, "Eventos");
//     data.win, key_hook, &data);
//     mlx_loop(data.mlx);
//     return (0);
// }