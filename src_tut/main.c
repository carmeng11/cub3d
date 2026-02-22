
#include "cub3d.h"

// Función que dibuja un píxel individual en la imagen
// void	put_pixel(int x, int y, int color, t_game *game)
// {
// 	// Verificar que el píxel esté dentro de los límites de la pantalla
// 	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// 		return;
	
// 	// Calcular el índice en el array de datos de la imagen
// 	// y * line_len: avanza a la fila correcta
// 	// x * bpp / 8: avanza a la columna correcta (bpp = bits por píxel)
// 	int	index = y * game->line_len + x * game->bpp / 8;
	
// 	// Asignar los 3 componentes del color (BGRA format en little endian) 0x00FF00
// 	game->data[index] = color & 0xFF;           // Componente Azul (B)
// 	game->data[index + 1] = (color >> 8) & 0xFF;  // Componente Verde (G)
// 	game->data[index + 2] = (color >> 16) & 0xFF; // Componente Rojo (R)
// }

//ADAPTACION DE MI FUNCION
void    put_pixel(int x, int y, int color, t_game *game)
{
    char    *dst;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;

    // Calcular la posición del píxel en memoria
    dst = game->data + (y * game->line_len + x * (game->bpp / 8));
	// Escribir el color en esa posición
    *(unsigned int*)dst = color;
}
//pintamos cuadrado sin relleno, solo bordes
void	draw_square(int x, int y, int size, int color, t_game *game)
{
	//pintamos la línea superior
	int	i;
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);//pintamos la línea horizontal primera
		put_pixel(x + i, y + size, color, game);//pintamos la línea horizontal segunda
		put_pixel(x, y + i, color, game);//pintamos la línea vertical izda
		put_pixel(x + size, y + i, color, game);//pintamos la línea vertical dcha
		i++;
	}
}
//pintamos cuadrado con relleno
// void    draw_square(int x, int y, int size, int color, t_game *game)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	while (i < size) // Recorre filas del cuadrado
// 	{
// 		j = 0;
// 		while (j < size) // Recorre columnas del cuadrado
// 		{
// 			put_pixel(x + j, y + i, color, game);
// 			//dibuja un pixel en la posición exacta (x, y)
// 			j++;
// 		}
// 		i++;
// 	}
// }

//	version con struct t_rec al no poder poner 5 args en la función po norminette
// void    draw_square(t_rec *rec, int color, t_game *game)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;

// 	x = rec->x * BLOCK;
// 	y = rec->y * BLOCK;

// 		i = 0;
// 	while (i < rec->size) // Recorre filas del cuadrado
// 	{
// 		j = 0;
// 		while (j < rec->size) // Recorre columnas del cuadrado
// 		{
// 			put_pixel(x + j, y + i, color, game);
// 			//dibuja un pixel en la posición exacta (x, y)
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	int		color;
	char	**map;

	color = 0xFF0000;
	map = game->map;
	y = 0;
	while (map[y] != NULL)//recorremos las filas hasta el último puntero nulo de cuando se hizo el malloc con tantos punteros como n de filas más uno
	//while (map[y])
	{
		x = 0;
		//while (map[x] != NULL) //recorremos las columnas esto no estaría correcto 
		while (map[y][x] != '\0') //recorremos cada una de las filas hasta el carácter nulo del final
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
				//si quiero que el mapa no esté exactamente en 0,0 sumaría a
				//x * BLOCK, y * BLOCK  10, 20, etc...
				//x * BLOCK + 20, y * BLOCK + 20
			x++;
		}
		y++;
	}
}

// void	draw_map(t_game *game)
// {
// 	t_rec	rec;

// 	int		color;
// 	char	**map;

// 	color = 0x0000FF;
// 	map = game->map;
// 	rec.y = 0;
// 	while (map[rec.y] != NULL)//recorremos las filas
// 	//while (map[y])
// 	{
// 		rec.x = 0;
// 		//while (map[x] != NULL) //recorremos las columnas
// 		while (map[rec.y][rec.x])
// 		{
// 			if (map[rec.y][rec.x] == '1')
// 				draw_square(&rec, color, game);
// 			rec.x++;
// 		}
// 		rec.y++;
// 	}
// }
void clear_image(t_game *game)
{
    int y;  // Contador de filas
    int x;  // Contador de columnas

    // Recorrer TODA la pantalla (cada píxel)
    y = 0;
    while (y < HEIGHT)  // Para cada fila (de 0 a 719)
    {
        x = 0;
        while (x < WIDTH)  // Para cada columna (de 0 a 1279)
        {
            // Poner el píxel en negro (0x000000)
            // Esto "borra" lo que había antes,lo pone a negro
            put_pixel(x, y, 0, game);
            x++;
        }
        y++;
    }
}


// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	// float	ray_x;
// 	// float	ray_y;
// 	// float	cos_angle;
// 	// float	sin_angle;
	
// 	player = &game->player;
// 	move_player(player);
// 	clear_image(game);
// 	draw_square(player->x, player->y, 10, 0x00FF00, game);
// 	draw_map(game);
// 	// ray_x = player->x;
// 	// ray_y = player->y;
// 	// cos_angle = cos(player->angle);
// 	// sin_angle = sin(player->angle);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (0);
// }

// Función que verifica si el rayo ha tocado una pared
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK; //px es la posición del pixel
	//si block es 64 y el ancho es 1280 1280 / 64 = 20
	//mi mapa es de 10, puedo dibujarlo hasta 20 sin salirme en ancho
	y = py / BLOCK;
	
	// Verificar límites del mapa primero (evitar seg fault)
	if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
		return (true);  // Fuera de pantalla = pared
	
	// Verificar límites del array del mapa
	if (game->map[y] == NULL)
		return (true);  // No hay más filas = pared
	
	if (x < 0 || game->map[y][x] == '\0')
		return (true);  // Fuera de la fila = pared
	
	// Verificar si es una pared
	if (game->map[y][x] == '1')
		return (true);
	
	return (false);
}
// int	draw_loop(t_game *game)
// {
// 	//t_player	*player;//version con puntero local
// 	// float	ray_x;
// 	// float	ray_y;
// 	// float	cos_angle;
// 	// float	sin_angle;
	
// 	//player = &game->player;
// 	move_player(&game->player);
// 	clear_image(game);
// 	draw_square(game->player.x, game->player.y, 10, 0XA020F0, game);//pintamos el cuadrado del judador rojo
// 	draw_map(game);//llamamos a la función que dibuja el mapa
	
// 	// Dibujar el rayo en la dirección que mira el jugador
// 	game->ray.ray_x = game->player.x;
// 	game->ray.ray_y = game->player.y;
// 	game->ray.cos_dir= cos(game->player.angle);
// 	game->ray.sin_dir= sin(game->player.angle);
	
// 	// El rayo avanza en la dirección del ángulo
// 	while (!touch(game->ray.ray_x, game->ray.ray_y, game))
// 	{
// 		put_pixel(game->ray.ray_x, game->ray.ray_y, 0x00FF00, game);  // Verde
// 		game->ray.ray_x += game->ray.sin_dir;
// 		game->ray.ray_y -= game->player.sin_angle;  // Y invertido (igual que el movimiento)
// 	}
	
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (0);
// }

// VERSION CON PUNTERO LOCAL (más limpia):

// ==================== CÁLCULO DE DISTANCIA EUCLIDIANA ====================
// Calcula la distancia real entre dos puntos usando el teorema de Pitágoras
// Ejemplo: Si el rayo recorre x=3 píxeles y y=4 píxeles
// → distancia = √(3² + 4²) = √(9 + 16) = √25 = 5 píxeles
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

// ==================== ALGORITMO DE RAYCASTING (tipo DDA) ====================
// Esta función dibuja UNA COLUMNA VERTICAL de la pantalla (3D)
// Parámetros:
//   - start_x: Ángulo del rayo actual
//   - i: Columna de la pantalla donde dibujar (0 a WIDTH-1)
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	// ===== PASO 1: INICIALIZAR EL RAYO =====
	// Calcular la dirección del rayo según el ángulo
	player->cos_angle = cos(start_x);  // Componente X de la dirección
	player->sin_angle = sin(start_x);  // Componente Y de la dirección
	
	// El rayo comienza en la posición del jugador
	player->ray_x = player->x;
	player->ray_y = player->y;
	
	// ===== PASO 2: ALGORITMO DDA (Digital Differential Analyzer) =====
	// Avanzar el rayo píxel a píxel hasta tocar una pared
	// Este es el núcleo del algoritmo DDA:
	// - Avanza en pequeños incrementos (cos_angle, sin_angle)
	// - En cada paso verifica si ha tocado una pared
	// Ejemplo: Si cos_angle=0.8 y sin_angle=0.6
	//   Iteración 1: ray_x += 0.8, ray_y -= 0.6 → posición (x+0.8, y-0.6)
	//   Iteración 2: ray_x += 0.8, ray_y -= 0.6 → posición (x+1.6, y-1.2)
	//   ...continúa hasta tocar pared
	while (!touch(player->ray_x, player->ray_y, game))
	{
		//
		
		
		//put_pixel(player->ray_x, player->ray_y, 0xFF0000, game); //dibuja el rayo rojo (visualización)
		player->ray_x += player->cos_angle;  // Avanzar en X
		player->ray_y -= player->sin_angle;  // Avanzar en Y (invertido porque pantalla crece hacia abajo)
	}
	
	// ===== PASO 3: CALCULAR DISTANCIA A LA PARED =====
	// Distancia = diferencia entre posición final del rayo y posición del jugador
	// Ejemplo: Jugador en (100, 100), rayo toca pared en (103, 104)
	//   → dist = √((103-100)² + (104-100)²) = √(9 + 16) = √25 = 5 píxeles
	float	dist = distance(player->ray_x - player->x, player->ray_y - player->y);
	
	// ===== PASO 4: CALCULAR ALTURA DE LA PARED EN PANTALLA =====
	// 🔥 FÓRMULA CLAVE DE PROYECCIÓN 3D:
	// height = (TAMAÑO_REAL_PARED / distancia) * FACTOR_PERSPECTIVA
	//
	// ¿Por qué funciona?
	// - Cuanto MÁS CERCA está la pared (dist pequeño) → altura GRANDE
	// - Cuanto MÁS LEJOS está la pared (dist grande) → altura PEQUEÑA
	// - Es una proyección en perspectiva (objetos cercanos parecen más grandes)
	//
	// Desglose de la fórmula:
	// - BLOCK (64): Tamaño real de un bloque en píxeles
	// - dist: Distancia calculada al punto de impacto
	// - WIDTH/2 (640): Factor de escala para ajustar la altura a la pantalla
	//
	// Ejemplo 1 (PARED CERCA):
	//   dist = 50 píxeles
	//   height = (64 / 50) * 640 = 1.28 * 640 = 819 píxeles
	//   → Pared MUY ALTA (casi llena la pantalla de 720px)
	//
	// Ejemplo 2 (PARED LEJOS):
	//   dist = 400 píxeles
	//   height = (64 / 400) * 640 = 0.16 * 640 = 102 píxeles
	//   → Pared PEQUEÑA (solo ocupa el centro)
	float	height = (BLOCK / dist) * (WIDTH / 2);
	
	// ===== PASO 5: CENTRAR LA PARED VERTICALMENTE =====
	// La pared debe dibujarse en el centro vertical de la pantalla
	// Si HEIGHT=720 y height=300:
	//   start_y = (720 - 300) / 2 = 210
	//   end = 210 + 300 = 510
	//   → La pared se dibuja de píxel 210 a 510 (centrada)
	int	start_y = (HEIGHT - height) / 2;  // Píxel superior de la pared
	int	end = start_y + height;             // Píxel inferior de la pared
	
	// ===== PASO 6: DIBUJAR LA COLUMNA VERTICAL =====
	// Dibujar una línea vertical en la columna 'i' de la pantalla
	// desde start_y hasta end con color azul
	while (start_y < end)
	{
		put_pixel(i, start_y, 0xFF0000, game);  // Columna i, fila start_y
		start_y++;
	}
}
// ==================== BUCLE PRINCIPAL DE RAYCASTING ====================
// Esta función se ejecuta en cada frame (60 veces por segundo aprox.)
// Renderiza toda la vista 3D lanzando WIDTH rayos (1280 rayos, uno por columna)
int	draw_loop(t_game *game)
{
	t_player	*player;
	
	player = &game->player;
	move_player(player);    // Actualizar posición según teclas presionadas
	clear_image(game);      // Limpiar pantalla (poner todo en negro)
	// draw_square(player->x, player->y, 10, 0XA020F0, game); // Dibujar jugador (minimap)
	// draw_map(game);         // Dibujar mapa 2D (minimap)
	
	// ===== CONFIGURACIÓN DEL CAMPO DE VISIÓN (FOV) =====
	// FOV = 60° (PI/3 radianes) es el campo de visión total
	// Este es el ángulo que abarca lo que el jugador puede ver
	//
	// ¿Por qué PI/3?
	// - PI/3 radianes = 60 grados
	// - Es un FOV típico en videojuegos (similar a la visión humana enfocada)
	//
	// fraction = ángulo entre cada rayo
	// Ejemplo: FOV 60° dividido en 1280 rayos
	//   → fraction = 60° / 1280 = 0.046875° por rayo
	float	fraction = PI / 3 / WIDTH;  // Incremento angular entre rayos consecutivos
	
	// ===== ÁNGULO INICIAL (BORDE IZQUIERDO DE LA PANTALLA) =====
	// Si el jugador mira en ángulo θ (player->angle):
	// - Lo que el jugador ve a su IZQUIERDA (gira +30° antihorario): θ + 30°
	// - Lo que el jugador ve a su DERECHA (gira -30° horario): θ - 30°
	// - Lo que el jugador ve al CENTRO: θ
	//
	// Ejemplo visual (jugador mirando al Norte = 90° = PI/2):
	//   Izquierda del jugador: 90° + 30° = 120° (Oeste) ←
	//   Centro del jugador:    90°                (Norte) ↑
	//   Derecha del jugador:   90° - 30° = 60°    (Este)  →
	//
	// IMPORTANTE: El píxel 0 (borde IZQUIERDO de pantalla) debe mostrar
	// lo que está a la IZQUIERDA del jugador → ángulo más alto
	float	start_x = player->angle + PI / 6;  // PI/6 = 30 grados
	
	// ===== LANZAR UN RAYO POR CADA COLUMNA DE LA PANTALLA =====
	// WIDTH = 1280 píxeles → lanzamos 1280 rayos
	// Cada rayo dibuja UNA columna vertical del efecto 3D
	//
	// Iteración 0: Rayo en ángulo (player->angle + 30°) → dibuja columna 0 (izquierda pantalla = izquierda jugador)
	// Iteración 1: Rayo en ángulo (player->angle + 29.95°) → dibuja columna 1
	// ...
	// Iteración 640: Rayo en ángulo (player->angle) → dibuja columna central
	// ...
	// Iteración 1279: Rayo en ángulo (player->angle - 30°) → dibuja columna 1279 (derecha pantalla = derecha jugador)
	int	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);  // Lanzar rayo en ángulo 'start_x', dibujar en columna 'i'
		start_x -= fraction;  // DECREMENTAR ángulo (de izquierda a derecha del jugador)
		i++;
	}
	
	// Mostrar la imagen final en la ventana
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main(void)
{
	t_game	game;
	int	size;
	size = 40;
	game.name = "Mi Primer Cub3D";
	game_init(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game.player);//pulsar tecla
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_release, &game.player);//soltar tecla
	mlx_hook(game.win, DestroyNotify,//Este evento se activa cuando la ventana se cierra. Llama a la función close_handler,
			//que generalmente se usa para liberar recursos o cerrar la aplicación correctamente.
			StructureNotifyMask,
			game_destroy,
			&game);

	// while (size > 0)
	// {
	 	draw_square(WIDTH / 2, HEIGHT / 2, size, 0XA020F0, &game);//dibujamos el cuadrado del jugador
	//  	size--;
	// }
	//mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);  // Mostrar la imagen DESPUÉS de dibujar
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

// Usuario presiona W:
//   → KeyPress se activa
//   → key_press(XK_w, &player) se ejecuta
//   → player->key_up = true
//   → El personaje EMPIEZA a moverse hacia arriba

// Usuario suelta W:
//   → KeyRelease se activa
//   → key_release(XK_w, &player) se ejecuta
//   → player->key_up = false
//   → El personaje DEJA de moverse hacia arriba

