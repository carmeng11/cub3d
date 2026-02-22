/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmen <carmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:52 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/21 22:41:57 by carmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_game(t_game *game)
{
	int		i;
	float	fraction;
	float	start_x;

	move_player(game);
	clear_image(game);
	// draw_minimap(game);
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
