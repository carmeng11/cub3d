/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmen <carmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:38:00 by cagomez-          #+#    #+#             */
/*   Updated: 2026/02/22 16:06:49 by carmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <X11/X.h>      // Para KeyPress, DestroyNotify, etc.
# include <X11/keysym.h> // Para XK_Escape, XK_w, etc.
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define BUFFER_SIZE 10
# define BLOCK 64
# define MAX_ITER 1000
// #define LEFT 65361
// #define RIGHT 65363
# define PI 3.14159265359
# define MOVE_SPEED 3.0
# define ROTATE_SPEED 0.03

// Estructura para las texturas (rutas a archivos .xpm)
typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_textures;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			color;
	// double		pos_x;
	// double		pos_y;
	char		start_dir;
}				t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
	// float		ray_x;
	// float		ray_y;
	float		cos_angle;
	float		sin_angle;
	}				t_player;
	
typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	cos_dir;
	float	sin_dir;
}			t_ray;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*name;
	t_map		map;
	t_img		img;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_ray		ray;
}				t_game;

typedef struct s_rect
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_rect;

// Funciones de parsing
int				parse_cub_file(char *filename, t_game *game);
int				parse_texture_line(char *line, char **texture);
int				parse_color_line(char *line, t_color *color);
void			print_error(char *message);

// Funciones de dibujo
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			draw_square(t_img *img, t_rect rect);
void			draw_minimap(t_game *game);
void			init_map(t_game *game);
void			map_draw(t_game *game);
void			clear_image(t_game *game);

// Funciones de inicialización
void			data_init(t_game *game);
void			game_init(t_game *game);

// Funciones de eventos
// int			key_hook(int keycode, t_game *game);
int				close_window(t_game *game);
void			events_init(t_game *game);
void			game_destroy(t_game *game);
int				render_game(t_game *game);

// Funciones de movimiento
int				can_move(t_game *game, double new_x, double new_y);
int				key_press(int keycode, t_game *game); // Si usas Opción 2
int				key_release(int keycode, t_game *game);
void			move_player(t_game *game);

// Funciones de utils
char			*get_next_line(int fd);
char			*ft_strdup_gnl(char *str);

// Raycasting
bool			touch(float ray_x, float ray_y, t_game *game);
float			distance(float x, float y);
void			cast_ray(t_game *game, float start_x, int i);

#endif