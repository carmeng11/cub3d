#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <fcntl.h>
#include <X11/keysym.h>  // Para XK_Escape, XK_w, etc.
#include <X11/X.h>        // Para KeyPress, DestroyNotify, etc.

#define WIDTH	1280
#define	HEIGHT	720
#define BLOCK 64
// #define LEFT 65361
// #define RIGHT 65363
#define PI 3.14159265359


typedef struct s_map
{
    char    **grid;      // Matriz del mapa
    int     width;       // Ancho
    int     height;      // Alto
	int		color;
    double  posX;        // Posición inicial X
    double  posY;        // Posición inicial Y
    char    start_dir;   // N, S, E, W
}   t_map;

// typedef struct s_img
// {
// 	void	*img_ptr;		// Puntero a la imagen (mlx_new_image)
// 	char	*pixels_ptr;	// Dirección de memoria de los píxeles (mlx_get_data_addr)
// 	int		bpp;			// Bits por píxel
// 	int		line_len;		// Bytes por línea
// 	int		endian;			// Orden de bytes
// }				t_img;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	float	ray_x;  //utilizamos float y no double pq no necesitamos tanta precisión y es más eficiente
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	//     double  posX;       // ✅ Ya lo tienes en map
//     double  posY;       // ✅ Ya lo tienes en map
//     double  dirX;       // ❌ FALTA - Dirección del vector (raycasting)
//     double  dirY;       // ❌ FALTA - Dirección del vector (raycasting)
//     double  planeX;     // ❌ FALTA - Plano de la cámara (raycasting)
//     double  planeY;     // ❌ FALTA - Plano de la cámara (raycasting)
}   t_player;

typedef	struct s_rec
{
	int	x;
	int	y;
	int	size;
}		t_rec;

typedef struct s_game
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*data;
	char	*name;
	int		bpp;			// Bits por píxel
	int		line_len;		// Bytes por línea
	int		endian;			// Orden de bytes
	char	**map;
	int	color;
    //t_map	map; //PONERLO LUEGO LO QUITO POR SEGUIR TUTORIAL
	//t_img	img;
	//A FUTURO
	t_player    player;  // ❌ FALTA - Para el raycasting
}   t_game;

// Funciones de parsing
int     parse_cub_file(char *filename, t_map *map);

// Funciones de dibujo
// void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
// void    draw_square(t_img *img, int x, int y, int size, int color);
void    draw_minimap(t_game *game);

void	map_draw(t_game *game);
//funciones que están en el main, dibujar el pixel, cuadrado sin relleno y cuadrado con relleno
void    put_pixel(int x, int y, int color, t_game *game);
void    draw_square(int x, int y, int size, int color, t_game *game);
//void    draw_square(t_rec *rec, int color, t_game *game);
void    draw_square_filled(int x, int y, int size, int color, t_game *game);
void    clear_image(t_game *game);
//int   draw_loop(t_game *game);

// Funciones de inicialización
void	game_init(t_game *game);
///void    init_map(t_game *game);
//char	**get_map(void);

// Funciones de eventos
int     key_hook(int keycode, t_game *game);
int     close_window(t_game *game);
void	events_init(t_game *game);
int		game_destroy(t_game *game);
void    render_game(t_game *game);

// Player FUNCIONES DEL TUTORIAL
void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player);

// Funciones de movimiento
int     can_move(t_game *game, double new_x, double new_y);
void    handle_movement(t_game *game, int keycode);  // Si usas Opción 2
#endif