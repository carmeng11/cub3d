/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:43 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/15 19:15:42 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	t_rect	rect;
	
	rect.x = (int)game->player.x - 5;
	rect.y = (int)game->player.y - 5;
	rect.size = 10;
	rect.color = 0x00FF00;
	draw_square(&game->img, rect);
}

void	draw_minimap(t_game *game)
{
	t_rect	rect;
	int		x;
	int		y;

	y = 0;
	while (game->map.grid[y] != NULL)
	{
		x = 0;
		while (game->map.grid[y][x] != '\0')
		{
			rect.x = x * BLOCK;
			rect.y = y * BLOCK;
			rect.size = BLOCK;
			if (game->map.grid[y][x] == '1')
				rect.color = 0x0000FF;
			else
				rect.color = 0x000000;
			draw_square(&game->img, rect);
			x++;
		}
		y++;
	}
	draw_player(game);
}

void	draw_square(t_img *img, t_rect rect)
{
	int	i;

	i = 0;
	while (i < rect.size)
	{
		my_mlx_pixel_put(img, rect.x + i, rect.y, rect.color);
		my_mlx_pixel_put(img, rect.x + i, rect.y + rect.size - 1, rect.color);
		my_mlx_pixel_put(img, rect.x, rect.y + i, rect.color);
		my_mlx_pixel_put(img, rect.x + rect.size - 1, rect.y + i, rect.color);
		i++;
	}
}
