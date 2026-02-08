#include "cub3d.h"

// Manejo de eventos de sistema (hooks, cerrar ventana)

int	close_window(t_game *game)
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
	// Evento de teclado tecola presionada
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
    // Evento de teclado tecola soltada
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	// Evento de cerrar ventana (X roja)
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, close_window, game);
	// Futuro: mlx_hook para ratón, redibujado, etc.
    // Loop hook (renderizado constante)
	//draw_square(&game->img, WIDTH / 2, HEIGHT / 2, 20, 0XA020F0);
	mlx_loop_hook(game->mlx, render_game, game);
}
// En events.c


// Función auxiliar para manejar movimiento
int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_w)
	{
		// new_y -= 0.5;
		game->player.key_up = true;
		//printf("W presionado\n"); 
	}
	if (keycode == XK_s)
		// new_y += 0.5;
		game->player.key_down = true;
	if (keycode == XK_a)
		// new_x -= 0.5;
		game->player.key_left = true;
	if (keycode == XK_d)
		//new_x += 0.5;
        game->player.key_right = true;
    // Flechas rotación
    if (keycode == XK_Left)
		game->player.left_rotate = true;
	if (keycode == XK_Right)
		game->player.right_rotate = true;
        //game->player.key_right = true;
	return (0); // No es una tecla de movimiento
    //PREGUNTAR POR ESTO
	// if (can_move(game, new_x, new_y))
	// {
	// 	game->map.posX = new_x;
	// 	game->map.posY = new_y;
	// 	render_game(game);
	// }
}

int key_release(int keycode, t_game *game)
{
    if (keycode == XK_w)
	{
		game->player.key_up = false;
		//printf("W soltado - key_up = false\n");
	}
    if (keycode == XK_s)
        game->player.key_down = false;
    if (keycode == XK_a)
        game->player.key_left = false;
    if (keycode == XK_d)
        game->player.key_right = false;
    if (keycode == XK_Left)
        game->player.left_rotate = false;
    if (keycode == XK_Right)
        game->player.right_rotate = false;
    
    return (0); 
}

// key_hook queda limpio

//KEY_HOOK SE ELIMINA PQ ESC LO MANEJO DENTRO DE KEY_PRESS
// int	key_hook(int keycode, t_game *game)
// {
// 	if (keycode == XK_Escape)
// 		close_window(game);
// 	else
// 		key_press(game, keycode);

// 	return (0);
// }