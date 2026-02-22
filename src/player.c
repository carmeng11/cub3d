/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmen <carmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:47 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/21 21:03:00 by carmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_rotation(t_game *game)
{
	t_player	*p;
	
	p = &game->player;
	if (p->left_rotate)
		p->angle += ROTATE_SPEED;
	if (p->right_rotate)
		p->angle -= ROTATE_SPEED;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
	p->cos_angle = cos(p->angle);
	p->sin_angle = sin(p->angle);
}

static void	move_dir(t_game *game, float dir_x, float dir_y)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + dir_x * MOVE_SPEED;
	new_y = game->player.y + dir_y * MOVE_SPEED;
	if (can_move(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	handle_movement(t_game *game)




{
	t_player	*p;
	
	p = &game->player;
	if (p->key_up)
		move_dir(game, p->cos_angle, -p->sin_angle);
	if (p->key_down)
		move_dir(game, -p->cos_angle, p->sin_angle);
	if (p->key_left)
		move_dir(game, -p->sin_angle, -p->cos_angle);
	if (p->key_right)
		move_dir(game, p->sin_angle, p->cos_angle);
}

void	move_player(t_game *game)
{
	handle_rotation(game);
	handle_movement(game);
}

int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_x >= game->map.width)
		return (0);
	if (map_y < 0 || map_y >= game->map.height)
		return (0);
	if (game->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}
