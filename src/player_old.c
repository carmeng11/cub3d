#include "cub3d.h"

// void	move_player(t_game *game)
// {
// 	int		speed;
// 	float	angle_speed;
// 	// float	cos_angle;
// 	// float	sin_angle;
// 	t_player	*p;

// 	p = &game->player;
// 	speed = 3;
// 	angle_speed = 0.03;
// 	// Precalcular cos y sin del ángulo actual (optimización)
// 	// Esto evita calcular cos/sin múltiples veces en cada frame
// 	p->cos_angle = cos(p->angle);  // Componente X del vector de dirección
//     p->sin_angle = sin(p->angle);  // Componente Y del vector de dirección
	
// 	// ===== ROTACIÓN (cambiar la dirección en la que mira el jugador) =====
// 	//EL JUGADOR PARTE MIRANDO AL NORTE, EL ANGULO ES PI / 2 90 GRADOS. SI DOY TECLA DCHA DECRECE Y EL RAYO QUEDA ENTRE 0 Y 90 GRADOS
// 	// El ángulo determina hacia dónde apunta el rayo (la vista del jugador)
// 	if (p->left_rotate) //si pulsamos tecla ixda el ángulo crece en sentido antihorario
// 		p->angle += angle_speed;  // ← Flecha izquierda: girar vista a la izquierda
// 	if (p->right_rotate) //si pulsamos tecla dcha el ángulo decrece, se resta en sentido horario
// 		p->angle -= angle_speed;  // → Flecha derecha: girar vista a la derecha
	
// 	// Normalizar el ángulo para mantenerlo entre 0 y 2π (0° y 360°)
// 	// Esto evita que el ángulo crezca infinitamente
// 	if (p->angle > 2 * PI) //sinifica que ha dado una vuelta completa, es mayor a 360
// 	//por ejmplo si es 380 como es mayor le resto 360 y el angulo es 20 que es el mismo
// 	//que 380, pero sin dar vuelta, siempre se mantienen los angulos entre 0 y 360
// 		p->angle -= 2 * PI;  // Si pasa de 360°, vuelve a 0°
// 	if (p->angle < 0)
// 	//si es negativo, p.e. -20 esto es como 340 -20 + 360 = 340 hacemos el angulo positivo
// 		p->angle += 2 * PI;  


		

// 	// ===== ADELANTE (W) - Mover en la dirección del rayo =====
// 	// El jugador avanza siguiendo la dirección del rayo (donde mira)
// 	// cos(angle) = cuánto se mueve en X (horizontal)
// 	// sin(angle) = cuánto se mueve en Y (vertical)
// 	// Y se resta porque en pantalla Y crece hacia abajo (0 arriba, 720 abajo)
// 	if (p->key_up)
// 	{
// 		p->x += p->cos_angle * speed;  // Componente horizontal del movimiento
// 		p->y -= p->sin_angle * speed;  // Componente vertical (Y invertido en pantalla)
// 		//antes estaba player->y -= speed;
// 	}
	
// 	// ===== ATRÁS (S) - Retroceder (dirección opuesta al rayo) =====
// 	// Es exactamente lo contrario de avanzar
// 	if (p->key_down)
// 	{
// 		p->x -= p->cos_angle * speed;  // Retrocede en X
// 		p->y += p->sin_angle * speed;  // Retrocede en Y
// 	}
	
// 	// ===== IZQUIERDA (A) - Movimiento lateral izquierdo (strafe) =====
// 	// Moverse perpendicular a la dirección del rayo (90° a la izquierda)
// 	// Para obtener la dirección perpendicular, intercambiamos sin/cos
// 	// Es como si girarás el vector de dirección 90°
// 	if (p->key_left)
// 	{
// 		p->x -= p->sin_angle * speed;  // Perpendicular: sin en vez de cos
// 		p->y -= p->cos_angle * speed;  // Perpendicular: cos en vez de sin
// 	}
	
// 	// ===== DERECHA (D) - Movimiento lateral derecho (strafe) =====
// 	// Moverse perpendicular a la dirección del rayo (90° a la derecha)
// 	// Es lo opuesto al movimiento lateral izquierdo
// 	if (p->key_right)
// 	{
// 		p->x += p->sin_angle * speed;  // Perpendicular opuesto
// 		p->y += p->cos_angle * speed;  // Perpendicular opuesto
// 	}
// }

void move_player(t_game *game)
{
    t_player *p;
    float	new_x;
    float	new_y;
    
    p = &game->player;
    
    // Precalcular cos/sin
    p->cos_angle = cos(p->angle);
    p->sin_angle = sin(p->angle);
	  // 🧪 DEBUG: Ver ángulo en tiempo real
	static int frame_count = 0;
    if (frame_count++ % 60 == 0)  // Cada 60 frames
    {
        printf("Ángulo: %.2f° | cos: %.2f | sin: %.2f | Pos: (%.0f, %.0f)\n",
               p->angle * 180 / PI,  // Convertir a grados
               p->cos_angle,
               p->sin_angle,
               p->x, p->y);
    }
    
    // ===== ROTACIÓN =====
    if (p->left_rotate)
        p->angle += 0.05;
    if (p->right_rotate)
        p->angle -= 0.05;
    
    // Normalizar ángulo
    if (p->angle > 2 * PI)
        p->angle -= 2 * PI;
    if (p->angle < 0)
        p->angle += 2 * PI;
    
    // ===== ADELANTE (W) =====
    if (p->key_up)
    {
        new_x = p->x + p->cos_angle * 5;
        new_y = p->y - p->sin_angle * 5;
        if (can_move(game, new_x, new_y))
        {
            p->x = new_x;
            p->y = new_y;
        }
    }
    
    // ===== ATRÁS (S) =====
    if (p->key_down)
    {
        new_x = p->x - p->cos_angle * 5;
        new_y = p->y + p->sin_angle * 5;
        if (can_move(game, new_x, new_y))
        {
            p->x = new_x;
            p->y = new_y;
        }
    }
    
    // ===== IZQUIERDA (A) =====
    if (p->key_left)
    {
        new_x = p->x - p->sin_angle * 5;
        new_y = p->y - p->cos_angle * 5;
        if (can_move(game, new_x, new_y))
        {
            p->x = new_x;
            p->y = new_y;
        }
    }
    
    // ===== DERECHA (D) =====
    if (p->key_right)
    {
        new_x = p->x + p->sin_angle * 5;
        new_y = p->y + p->cos_angle * 5;
        if (can_move(game, new_x, new_y))
        {
            p->x = new_x;
            p->y = new_y;
        }
    }
}

//Lógica específica del jugador (movimiento, rotación, colisiones)

// Función auxiliar para validar movimiento VSLIDA COLISIONES
int can_move(t_game *game, double x, double y)
{
    int map_x;
    int map_y;
    
    // Convertir píxeles → celda del mapa
    map_x = (int)(x / BLOCK);
    map_y = (int)(y / BLOCK);
    
    // ✅ Verificar límites ANTES de acceder al array
    if (map_x < 0 || map_x >= game->map.width)
        return (0);
    if (map_y < 0 || map_y >= game->map.height)
        return (0);
    
    // ✅ Verificar si es pared
    if (game->map.grid[map_y][map_x] == '1')
        return (0);
    
    return (1);  // Puede moverse
}