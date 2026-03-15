/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:52 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 19:56:03 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
void	draw_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b;
	floor_color = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

int	render_game(t_game *game)
{
	int		i;
	float	fraction;
	float	start_x;

	move_player(game);
	clear_image(game);
	// draw_minimap(game);
	draw_ceiling_floor(game); // ← NUEVO: Dibuja techo y suelo
	fraction = PI / 3 / WIDTH;
	start_x = game->player.angle + PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(game, start_x, i);
		start_x -= fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

// void	clear_image(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			my_mlx_pixel_put(&game->img, x, y, 0x000000);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// FUNCION PARA OPTIMIZAR CLEAR IMAGE

void	clear_image(t_game *game)
{
	ft_memset(game->img.pixels_ptr, 0, WIDTH * HEIGHT * (game->img.bpp / 8));
}
