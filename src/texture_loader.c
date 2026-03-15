/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:55:00 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 19:48:37 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** normalize_path - Elimina "./" del inicio de la ruta si existe
**
** MLX tiene problemas con rutas relativas que empiezan por "./"
** Convertimos "./textures/north.xpm" → "textures/north.xpm"
**
** @path: Ruta original
** Return: Ruta normalizada (puede ser la misma si no empieza por "./")
*/
static char	*normalize_path(char *path)
{
    if (path[0] == '.' && path[1] == '/')
        return (path + 2);  // Saltamos los primeros 2 caracteres
    return (path);
}

/*
** load_single_texture - Carga UNA textura XPM en memoria
**
** Proceso:
** 1. Normalizar ruta (quitar "./" si existe)
** 2. mlx_xpm_file_to_image: Lee archivo XPM y crea imagen
** 3. mlx_get_data_addr: Obtiene array de píxeles de la imagen
** 4. Guarda width y height
**
** @game: Estructura del juego (necesitamos game->mlx)
** @path: Ruta del archivo XPM (ej: "./textures/north.xpm")
** @texture: Estructura donde guardar la textura cargada
** Return: 0 si OK, 1 si error
*/
static int	load_single_texture(t_game *game, char *path, t_texture *texture)
{
    char	*normalized_path;

    normalized_path = normalize_path(path);
    printf("  Cargando: %s → %s\n", path, normalized_path);
    
    // Cargar archivo XPM como imagen MLX
    texture->img.img_ptr = mlx_xpm_file_to_image(game->mlx, normalized_path,
        &texture->width, &texture->height);
    
    if (!texture->img.img_ptr)
    {
        printf("Error: Failed to load texture: %s\n", normalized_path);
        return (1);
    }
    
    // Obtener array de píxeles de la imagen
    texture->img.pixels_ptr = mlx_get_data_addr(texture->img.img_ptr,
        &texture->img.bpp, &texture->img.line_len, &texture->img.endian);
    
    if (!texture->img.pixels_ptr)
    {
        printf("Error: Failed to get texture data: %s\n", normalized_path);
        mlx_destroy_image(game->mlx, texture->img.img_ptr);
        return (1);
    }
    
    printf("  Loaded: %s (%dx%d, bpp=%d)\n", 
        normalized_path, texture->width, texture->height, texture->img.bpp);
    return (0);
}

/*
** load_textures - Carga las 4 texturas (N, S, E, W) en memoria
**
** Orden:
** loaded_tex[0] = North
** loaded_tex[1] = South  
** loaded_tex[2] = East
** loaded_tex[3] = West
**
** @game: Estructura del juego
** Return: 0 si OK, 1 si error
*/
int	load_textures(t_game *game)
{
    printf("\n Cargando texturas...\n");
    
    // Cargar textura NORTH
    if (load_single_texture(game, game->textures.north, &game->loaded_tex[0]))
        return (1);
    
    // Cargar textura SOUTH
    if (load_single_texture(game, game->textures.south, &game->loaded_tex[1]))
        return (1);
    
    // Cargar textura EAST
    if (load_single_texture(game, game->textures.east, &game->loaded_tex[2]))
        return (1);
    
    // Cargar textura WEST
    if (load_single_texture(game, game->textures.west, &game->loaded_tex[3]))
        return (1);
    
    printf(" Todas las texturas cargadas correctamente\n\n");
    return (0);
}

/*
** init_textures_and_events - Inicializa texturas y eventos
**
** @game: Estructura del juego
*/
void	init_textures_and_events(t_game *game)
{
    if (load_textures(game) != 0)
    {
        print_error("Failed to load textures");
        game_destroy(game);
        exit(1);
    }
    events_init(game);
}