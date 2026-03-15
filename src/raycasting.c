/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:17 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/11 18:25:54 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (true);
	if (game->map.grid[y] == NULL)
		return (true);
	if (game->map.grid[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float dx, float dy)
{
	double	dist;

	dist = (sqrt(dx * dx + dy * dy));
	return (dist);
}

void	draw_ray(t_game *game, float dist, int i)
{
	float	start_y;
	float	height;
	int		end;
	//int		tex_y;
	if (dist < 0.1)
		dist = 0.1;
	height = (BLOCK / dist) * (WIDTH / 2);
	if (height > HEIGHT * 2)
		height = HEIGHT * 2;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		if (start_y >= 0 && start_y < HEIGHT)
			my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
		// TEXTURAS
		// tex_y = calcular_coordenada_textura(start_y, height);
		// int color = obtener_pixel_textura(tex, tex_x, tex_y);
		start_y++;
	}
}

void	cast_ray(t_game *game, float start_x, int i)
{
	int		count;
	float	dist;

	game->ray.cos_dir= cos(start_x);
	game->ray.sin_dir= sin(start_x);
	game->ray.ray_x = game->player.x;
	game->ray.ray_y = game->player.y;
	count = 0;
	while (!touch(game->ray.ray_x, game->ray.ray_y, game) && count < MAX_ITER)
	{
		game->ray.ray_x += game->ray.cos_dir * 0.5;
		game->ray.ray_y -= game->ray.sin_dir * 0.5;
		count++;
	}
	if (count >= MAX_ITER)
		return ;
	dist = distance(game->ray.ray_x - game->player.x, game->ray.ray_y
			- game->player.y);
	dist = dist * cos(start_x - game->player.angle);
	draw_ray(game, dist, i);
}
