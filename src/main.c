/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:55:35 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/15 17:36:22 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", STDERR_FILENO);
		return (1);
	}
	if (parse_cub_file(argv[1], &game) != 0)
		return (1);
	game.name = "Cub3D";
	game_init(&game);
	return (0);
}
