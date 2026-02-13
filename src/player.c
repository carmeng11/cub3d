#include "cub3d.h"

void	handle_rotation(t_player *player)
{
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	// ===== ROTACIÓN =====
	if (player->left_rotate)
		player->angle += ROTATE_SPEED;
	if (player->right_rotate)
		player->angle -= ROTATE_SPEED;
	// Normalizar ángulo
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

static void	move_forward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + game->player.cos_angle * MOVE_SPEED;
	new_y = game->player.y - game->player.sin_angle * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	move_backward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x - game->player.cos_angle * MOVE_SPEED;
	new_y = game->player.y + game->player.sin_angle * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	move_left(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x - game->player.sin_angle * MOVE_SPEED;
	new_y = game->player.y - game->player.cos_angle * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	move_right(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + game->player.sin_angle * MOVE_SPEED;
	new_y = game->player.y + game->player.cos_angle * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
void	handle_movement(t_game *game)
{
	if (game->player.key_up)
		move_forward(game);
	if (game->player.key_down)
		move_backward(game);
	if (game->player.key_left)
		move_left(game);
	if (game->player.key_right)
		move_right(game);
}

void	move_player(t_game *game)
{
	handle_rotation(&game->player);
	handle_movement(game);
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