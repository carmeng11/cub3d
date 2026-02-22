/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:25 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/15 19:21:28 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	events_init(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, close_window, game);
	mlx_loop_hook(game->mlx, render_game, game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_w)
		game->player.key_up = true;
	if (keycode == XK_s)
		game->player.key_down = true;
	if (keycode == XK_a)
		game->player.key_left = true;
	if (keycode == XK_d)
		game->player.key_right = true;
	if (keycode == XK_Left)
		game->player.left_rotate = true;
	if (keycode == XK_Right)
		game->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->player.key_up = false;
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
