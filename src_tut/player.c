#include "cub3d.h"

int game_destroy(t_game *game)
{
	mlx_destroy_image(game->mlx,
		game->img);
	mlx_destroy_window(game->mlx,
		game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

// callback when a key is pressed
// Esta función se ejecuta automáticamente cuando el usuario PRESIONA una tecla
int	key_press(int keycode, t_player *player)
{
	// WASD - Movimiento del jugador
	if (keycode == XK_w)
		player->key_up = true;      // W = Avanzar hacia adelante (en dirección del rayo)
	if (keycode == XK_s)
		player->key_down = true;    // S = Retroceder (dirección opuesta al rayo)
	if (keycode == XK_a)
		player->key_left = true;    // A = Moverse lateral izquierda (perpendicular)
	if (keycode == XK_d)
		player->key_right = true;   // D = Moverse lateral derecha (perpendicular)
	
	// Flechas izquierda/derecha - Rotación de la vista
	if (keycode == XK_Left)
		player->left_rotate = true;  // ← = Girar vista a la izquierda
	if (keycode == XK_Right)
		player->right_rotate = true; // → = Girar vista a la derecha
	return (0);
}

// callback when a key is released
// Esta función se ejecuta automáticamente cuando el usuario SUELTA una tecla
int	key_release(int keycode, t_player *player)
{
	// Desactivar el flag correspondiente cuando se suelta la tecla
	// Esto permite que el jugador deje de moverse al soltar WASD
	if (keycode == XK_w)
		player->key_up = false;
	if (keycode == XK_s)
		player->key_down = false;
	if (keycode == XK_a)
		player->key_left = false;
	if (keycode == XK_d)
		player->key_right = false;
	
	// Desactivar rotación al soltar las flechas
	if (keycode == XK_Left)
		player->left_rotate = false;
	if (keycode == XK_Right)
		player->right_rotate = false;
	return (0);
}

// FUNCIÓN PARA VALIDAR COLISIONES (para cuando tengas el mapa parseado)
// Descomenta esto cuando implementes el parsing del .cub
// int can_move(t_game *game, double new_x, double new_y)
// {
//     int map_x = (int)new_x;
//     int map_y = (int)new_y;
    
//     if (map_x < 0 || map_x >= game->map.width)
//         return (0);
//     if (map_y < 0 || map_y >= game->map.height)
//         return (0);
//     if (game->map.grid[map_y][map_x] == 1)  // 1 = pared
//         return (0);
//     return (1);
// }


// VERSION CON COLISIONES (descomenta cuando tengas el mapa)
// void	move_player(t_player *player)
// {
// 	t_game	*game;

// 	int		speed;
// 	float	new_x;
// 	float	new_y;

// 	speed = 5;
// 	new_x = player->x;
// 	new_y = player->y;
	
// 	if (player->key_up)
// 		new_y -= speed;
// 	if (player->key_down)
// 		new_y += speed;
// 	if (player->key_left)
// 		new_x -= speed;
// 	if (player->key_right)
// 		new_x += speed;
	
// 	// Solo si hay mapa, validar colisiones
// 	if (game->map != NULL)
// 	{
// 		if (can_move(game, new_x, new_y))
// 		{
// 			player->x = new_x;
// 			player->y = new_y;
// 		}
// 	}
// 	else  // Si no hay mapa, movimiento libre
// 	{
// 		player->x = new_x;
// 		player->y = new_y;
// 	}
// }

// VERSION SIMPLE DEL TUTORIAL (movimiento con rotación corregido)
void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	// float	cos_angle;
	// float	sin_angle;

	speed = 3;
	angle_speed = 0.03;
	// Precalcular cos y sin del ángulo actual (optimización)
	// Esto evita calcular cos/sin múltiples veces en cada frame
	player->cos_angle = cos(player->angle);  // Componente X del vector de dirección
    player->sin_angle = sin(player->angle);  // Componente Y del vector de dirección
	
	// ===== ROTACIÓN (cambiar la dirección en la que mira el jugador) =====
	//EL JUGADOR PARTE MIRANDO AL NORTE, EL ANGULO ES PI / 2 90 GRADOS. SI DOY TECLA DCHA DECRECE Y EL RAYO QUEDA ENTRE 0 Y 90 GRADOS
	// El ángulo determina hacia dónde apunta el rayo (la vista del jugador)
	if (player->left_rotate) //si pulsamos tecla ixda el ángulo crece en sentido antihorario
		player->angle += angle_speed;  // ← Flecha izquierda: girar vista a la izquierda
	if (player->right_rotate) //si pulsamos tecla dcha el ángulo decrece, se resta en sentido horario
		player->angle -= angle_speed;  // → Flecha derecha: girar vista a la derecha
	
	// Normalizar el ángulo para mantenerlo entre 0 y 2π (0° y 360°)
	// Esto evita que el ángulo crezca infinitamente
	if (player->angle > 2 * PI) //sinifica que ha dado una vuelta completa, es mayor a 360
	//por ejmplo si es 380 como es mayor le resto 360 y el angulo es 20 que es el mismo
	//que 380, pero sin dar vuelta, siempre se mantienen los angulos entre 0 y 360
		player->angle -= 2 * PI;  // Si pasa de 360°, vuelve a 0°
	if (player->angle < 0)
	//si es negativo, p.e. -20 esto es como 340 -20 + 360 = 340 hacemos el angulo positivo
		player->angle += 2 * PI;  


		

	// ===== ADELANTE (W) - Mover en la dirección del rayo =====
	// El jugador avanza siguiendo la dirección del rayo (donde mira)
	// cos(angle) = cuánto se mueve en X (horizontal)
	// sin(angle) = cuánto se mueve en Y (vertical)
	// Y se resta porque en pantalla Y crece hacia abajo (0 arriba, 720 abajo)
	if (player->key_up)
	{
		player->x += player->cos_angle * speed;  // Componente horizontal del movimiento
		player->y -= player->sin_angle * speed;  // Componente vertical (Y invertido en pantalla)
		//antes estaba player->y -= speed;
	}
	
	// ===== ATRÁS (S) - Retroceder (dirección opuesta al rayo) =====
	// Es exactamente lo contrario de avanzar
	if (player->key_down)
	{
		player->x -= player->cos_angle * speed;  // Retrocede en X
		player->y += player->sin_angle * speed;  // Retrocede en Y
	}
	
	// ===== IZQUIERDA (A) - Movimiento lateral izquierdo (strafe) =====
	// Moverse perpendicular a la dirección del rayo (90° a la izquierda)
	// Para obtener la dirección perpendicular, intercambiamos sin/cos
	// Es como si girarás el vector de dirección 90°
	if (player->key_left)
	{
		player->x -= player->sin_angle * speed;  // Perpendicular: sin en vez de cos
		player->y -= player->cos_angle * speed;  // Perpendicular: cos en vez de sin
	}
	
	// ===== DERECHA (D) - Movimiento lateral derecho (strafe) =====
	// Moverse perpendicular a la dirección del rayo (90° a la derecha)
	// Es lo opuesto al movimiento lateral izquierdo
	if (player->key_right)
	{
		player->x += player->sin_angle * speed;  // Perpendicular opuesto
		player->y += player->cos_angle * speed;  // Perpendicular opuesto
	}
}	