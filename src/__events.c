#include "cub3d.h"

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

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
//VERSION SIMPLE KEY_HOOK
// int key_hook(int keycode, t_game *game)
// {
//     printf("Tecla presionada: %d\n", keycode); // Para ver códigos
    
//     if (keycode == XK_Escape)    // ESC
//         close_window(game);
//     if (keycode == XK_Up)        // Flecha arriba - avanzar
//         printf("Avanzar\n");
//     if (keycode == XK_Down)      // Flecha abajo - retroceder
//         printf("Retroceder\n");
//     if (keycode == XK_Left)      // Flecha izquierda - rotar izq
//         printf("Rotar izquierda\n");
//     if (keycode == XK_Right)     // Flecha derecha - rotar der
//         printf("Rotar derecha\n");
    
//     return (0);
// }

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    if (keycode == 119) // XK_w
        printf("Adelante\n");
    if (keycode == 115) // XK_s
        printf("Atrás\n");
    if (keycode == 97)  // XK_a
        printf("Izquierda\n");
    if (keycode == 100) // XK_d
        printf("Derecha\n");
    return (0);
}

//MVTO EN KEY_HOOK
// int key_hook(int keycode, t_game *game)
// {
// 	double new_x;  // ✅ Variable temporal para CALCULAR
//     double new_y;  // ✅ Variable temporal para CALCULAR
    
//     // Solo se usan para validar ANTES de mover
//     // NO necesitan estar en la estructura	
// 	if (keycode == XK_Escape)
// 		close_window(game);
	
// 	// Movimiento arriba (Norte)
// 	if (keycode == XK_Up)
// 	{
// 		new_x = game->map.posX;
// 		new_y = game->map.posY - 0.5;
// 		if (can_move(game, new_x, new_y))
// 		{
// 			game->map.posY = new_y;
// 			render_game(game);
// 		}
// 	}
	
// 	// Movimiento abajo (Sur)
// 	if (keycode == XK_Down)
// 	{
// 		new_x = game->map.posX;
// 		new_y = game->map.posY + 0.5;
// 		if (can_move(game, new_x, new_y))
// 		{
// 			game->map.posY = new_y;
// 			render_game(game);
// 		}
// 	}
	
// 	// Movimiento izquierda (Oeste)
// 	if (keycode == XK_Left)
// 	{
// 		new_x = game->map.posX - 0.5;
// 		new_y = game->map.posY;
// 		if (can_move(game, new_x, new_y))
// 		{
// 			game->map.posX = new_x;
// 			render_game(game);
// 		}
// 	}
	
// 	// Movimiento derecha (Este)
// 	if (keycode == XK_Right)
// 	{
// 		new_x = game->map.posX + 0.5;
// 		new_y = game->map.posY;
// 		if (can_move(game, new_x, new_y))
// 		{
// 			game->map.posX = new_x;
// 			render_game(game);
// 		}
// 	}
	
// 	return (0);
// }

// int	can_move(t_game *game, double new_x, double new_y)
// {
// 	int map_x;
// 	int map_y;
	
// 	map_x = (int)new_x;
// 	map_y = (int)new_y;
	
// 	// Verificar límites del mapa
// 	if (map_x < 0 || map_x >= game->map.width)
// 		return (0);
// 	if (map_y < 0 || map_y >= game->map.height)
// 		return (0);
	
// 	// Verificar si la nueva posición es una pared (1)
// 	if (game->map.grid[map_y][map_x] == 1)
// 		return (0);
	
// 	return (1);
// }
