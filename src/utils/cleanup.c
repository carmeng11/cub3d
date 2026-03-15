/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:50:00 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 15:21:22 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_map - Libera la memoria del mapa
**
** @game: Estructura del juego
*/
static void	free_map(t_game *game)
{
    int	i;

    if (!game->map.grid)
        return ;
    i = 0;
    while (game->map.grid[i])
    {
        free(game->map.grid[i]);
        i++;
    }
    free(game->map.grid);
    game->map.grid = NULL;
}

/*
** free_texture_paths - Libera las rutas de texturas
**
** @game: Estructura del juego
*/
void	free_texture_paths(t_game *game)
{
    if (game->textures.north)
    {
        free(game->textures.north);
        game->textures.north = NULL;
    }
    if (game->textures.south)
    {
        free(game->textures.south);
        game->textures.south = NULL;
    }
    if (game->textures.east)
    {
        free(game->textures.east);
        game->textures.east = NULL;
    }
    if (game->textures.west)
    {
        free(game->textures.west);
        game->textures.west = NULL;
    }
}
//LIBERAR CUANDO SE CIERRA EL MAPA
/*
** game_destroy - Libera todos los recursos del juego
**
** Orden de liberación:
** 1. Imagen principal
** 2. Ventana
** 3. Display MLX
** 4. Puntero MLX
** 5. Mapa
** 6. Rutas de texturas
**
** @game: Estructura del juego
*/
void	game_destroy(t_game *game)
{
    if (game->img.img_ptr)
        mlx_destroy_image(game->mlx, game->img.img_ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    free_map(game);
    free_texture_paths(game);
}