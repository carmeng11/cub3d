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
// #define LEFT 65361
// #define RIGHT 65363
# define PI 3.14159265359
# define MOVE_SPEED 3.0
# define ROTATE_SPEED 0.03

// Estructura para las texturas (rutas a archivos .xpm)
typedef struct s_textures
{
	char *north; // OBLIGATORIO Ruta a textura Norte NO ./path
	char *south; // OBLIGATORIO Ruta a textura Sur (SO)
	char *west;  // OBLIGATORIO Ruta a textura Oeste (WE)
	char *east;  // OBLIGATORIO Ruta a textura Este (EA)
}			t_textures;

// Estructura para los colores RGB
typedef struct s_color
{
	int r; // Red (0-255)
	int g; // Green (0-255)
	int b; // Blue (0-255)
}			t_color;

typedef struct s_map
{
	char **grid; // OBLIGATORIO Matriz del mapa
	int width;   // UTIL Ancho
	int height;  // UTIL Alto
	int		color;
	double posX;    // OBLIGATORIO Posición inicial X
	double posY;    // OBLIGATORIO Posición inicial Y
	char start_dir; // OBLIGATORIO N, S, E, W
}			t_map;

typedef struct s_img
{
	void *img_ptr;    // Puntero a la imagen (mlx_new_image)
	char *pixels_ptr; // Dirección de memoria de los píxeles (mlx_get_data_addr)
	int bpp;          // Bits por píxel
	int line_len;     // Bytes por línea
	int endian;       // Orden de bytes
}			t_img;

typedef struct s_player
{
	float x;     // Posición actual X (en píxeles)
	float y;     // Posición actual Y (en píxeles)
	float angle; // Ángulo de rotación (radianes)

	bool key_up;       // W presionado
	bool key_down;     // S presionado
	bool key_left;     // A presionado
	bool key_right;    // D presionado
	bool left_rotate;  // Flecha ← presionada
	bool right_rotate; // Flecha → presionada
	float	ray_x;
	float	ray_y;
	float cos_angle; // Precalculado (optimización)
	float sin_angle; // Precalculado (optimización)
}			t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*name;
	t_map	map;
	t_img	img;
	t_textures textures; // Texturas del archivo .cub
	t_color floor;       // Color del suelo (F)
	t_color ceiling;     // Color del techo (C)
	// A FUTURO
	t_player player; //  FALTA - Para el raycasting
}			t_game;

// A FUTURO
// typedef struct s_player
// {
//     double  posX;       //  Ya lo tienes en map
//     double  posY;       //  Ya lo tienes en map
//     double  dirX;       //  FALTA - Dirección del vector (raycasting)
//     double  dirY;       //  FALTA - Dirección del vector (raycasting)
//     double  planeX;     //  FALTA - Plano de la cámara (raycasting)
//     double  planeY;     // FALTA - Plano de la cámara (raycasting)
// }   t_player;

// Funciones de parsing
int			parse_cub_file(char *filename, t_game *game);
int			parse_texture_line(char *line, char **texture);
int			parse_color_line(char *line, t_color *color);
void		print_error(char *message);

// Funciones de dibujo
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_square(t_img *img, int x, int y, int size, int color);
void		draw_minimap(t_game *game);
void		init_map(t_game *game);
void		map_draw(t_game *game);
void		clear_image(t_game *game);

// Funciones de inicialización
void		data_init(t_game *game);
void		game_init(t_game *game);

// Funciones de eventos
// int			key_hook(int keycode, t_game *game);
int			close_window(t_game *game);
void		events_init(t_game *game);
void		game_destroy(t_game *game);
int			render_game(t_game *game);

// Funciones de movimiento
int			can_move(t_game *game, double new_x, double new_y);
int	key_press(int keycode, t_game *game); // Si usas Opción 2
int			key_release(int keycode, t_game *game);
void		move_player(t_game *game);

// Funciones de utils
char		*get_next_line(int fd);
char		*ft_strdup_gnl(char *str);

// Raycasting
bool    touch(float ray_x, float ray_y, t_game *game);
float   distance(float x, float y);
void	cast_ray(t_game *game, float start_x, int i);
void    render_3d(t_game *game);

#endif