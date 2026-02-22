/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmen <carmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:38 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/21 20:09:13 by carmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

static float	get_start_angle(char dir)
{
	if (dir == 'N')
		return (PI / 2);
	else if (dir == 'S')
		return (3 * PI / 2);
	else if (dir == 'W')
		return (PI);
	else if (dir == 'E')
		return (0);
	return (PI / 2);
}

void	init_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	// p->x = game->map.pos_x * BLOCK;
	// p->y = game->map.pos_y * BLOCK;
	p->x = game->map.width / 2 * BLOCK;
	p->y = game->map.height / 2 * BLOCK;
	p->angle = get_start_angle(game->map.start_dir);
	p->key_up = false;
	p->key_down = false;
	p->key_left = false;
	p->key_right = false;
	p->left_rotate = false;
	p->right_rotate = false;
}

void	init_map(t_game *game)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111111111111";
	map[1] = "10000000000000000001";
	map[2] = "10000000000000000001";
	map[3] = "10000000100000000001";
	map[4] = "10000000000000000001";
	map[5] = "10000010000000000001";
	map[6] = "10000000100000000001";
	map[7] = "10000000000000000001";
	map[8] = "10000000000000000001";
	map[9] = "11111111111111111111";
	map[10] = NULL;
	game->map.grid = map;
	game->map.width = 20;
	game->map.height = 10;
	// game->map.pos_x = game->map.width / 2;
	// game->map.pos_y = game->map.height / 2;
	game->map.start_dir = 'N';
}

void	game_init(t_game *game)
{
	init_map(game);
	init_player(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		malloc_error();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, game->name);
	if (game->win == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.img_ptr == NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		malloc_error();
	}
	game->img.pixels_ptr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	events_init(game);
	mlx_loop(game->mlx);
}
