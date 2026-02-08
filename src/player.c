#include "cub3d.h"

void	move_player(t_game *game)
{
	t_player	*p;
	float		new_x;
	float		new_y;

	p = &game->player;
	// Precalcular cos/sin
	p->cos_angle = cos(p->angle);
	p->sin_angle = sin(p->angle);
	// ===== ROTACIÓN =====
	if (p->left_rotate)
		p->angle += ROTATE_SPEED;
	if (p->right_rotate)
		p->angle -= ROTATE_SPEED;
	// Normalizar ángulo
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
	// ===== ADELANTE (W) =====
	if (p->key_up)
	{
		new_x = p->x + p->cos_angle * MOVE_SPEED;
		new_y = p->y - p->sin_angle * MOVE_SPEED;
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



// Función auxiliar para validar movimiento VALIDA COLISIONES
int	can_move(t_game *game, double x, double y)
{
	int map_x;
	int map_y;

	// Convertir píxeles → celda del mapa
	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);

	// Verificar límites ANTES de acceder al array
	if (map_x < 0 || map_x >= game->map.width)
		return (0);
	if (map_y < 0 || map_y >= game->map.height)
		return (0);

	// Verificar si es pared
	if (game->map.grid[map_y][map_x] == '1')
		return (0);

	return (1); // Puede moverse
}