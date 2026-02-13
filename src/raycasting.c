#include "cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK); // px es la posición del pixel
	// si block es 64 y el ancho es 1280 1280 / 64 = 20
	// mi mapa es de 10, puedo dibujarlo hasta 20 sin salirme en ancho
	y = (int)(py / BLOCK);
	// Verificar límites de ventana (seguridad extra)
	// if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
	// 	return (true);
	// Verificar límites del mapa primero (evitar seg fault)
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (true); // Fuera de pantalla = pared
	// Verificar límites del array del mapa
	if (game->map.grid[y] == NULL)
		return (true); // No hay más filas = pared
	// if (x < 0 || game->map.grid[y][x] == '\0')
	// 	return (true);  // Fuera de la fila = pared
	// Verificar si es una pared
	if (game->map.grid[y][x] == '1')
		return (true);
	return (false);
}

// EXPLICACION
// Rayo en píxel (192, 128)
// x = (int)(192 / 64) = 3  // Columna 3 del mapa
// y = (int)(128 / 64) = 2  // Fila 2 del mapa

// Verificar: game->map.grid[2][3]
// Si es '1' → return true (pared)
// Si es '0' → return false (espacio)

// PROBLEMA: Verificas px/py (píxeles) cuando deberías verificar x/y (celdas)
// if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)

// CORRECTO: Verificar x/y en el rango del mapa
// if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)

float	distance(float dx, float dy)
{
	return (sqrt(dx * dx + dy * dy));
}

// ==================== ALGORITMO DE RAYCASTING (tipo DDA) ====================
// Esta función dibuja UNA COLUMNA VERTICAL de la pantalla (3D)
// Parámetros:
//   - start_x: Ángulo del rayo actual
//   - i: Columna de la pantalla donde dibujar (0 a WIDTH-1)

//VERSION SEG FAULT
// void	cast_ray(t_game *game, float start_x, int i)
// {
// 	// ===== PASO 1: INICIALIZAR EL RAYO =====
// 	// Calcular la dirección del rayo según el ángulo
// 	game->player.cos_angle = cos(start_x); // Componente X de la dirección
// 	game->player.sin_angle = sin(start_x); // Componente Y de la dirección

// 	// El rayo comienza en la posición del jugador
// 	game->player.ray_x = game->player.x;
// 	game->player.ray_y = game->player.y;

// 	// ===== PASO 2: ALGORITMO DDA (Digital Differential Analyzer) =====
// 	// Avanzar el rayo píxel a píxel hasta tocar una pared
// 	// Este es el núcleo del algoritmo DDA:
// 	// - Avanza en pequeños incrementos (cos_angle, sin_angle)
// 	// - En cada paso verifica si ha tocado una pared
// 	// Ejemplo: Si cos_angle=0.8 y sin_angle=0.6
// 	//   Iteración 1: ray_x += 0.8, ray_y -= 0.6 → posición (x+0.8, y-0.6)
// 	//   Iteración 2: ray_x += 0.8, ray_y -= 0.6 → posición (x+1.6, y-1.2)
// 	//   ...continúa hasta tocar pared
// 	while (!touch(game->player.ray_x, game->player.ray_y, game))
// 	{
// 		//

// 		// put_pixel(player->ray_x, player->ray_y, 0xFF0000, game);
// 			//dibuja el rayo rojo (visualización)
// 		game->player.ray_x += game->player.cos_angle; // Avanzar en X
// 		game->player.ray_y -= game->player.sin_angle;
// 			// Avanzar en Y (invertido porque pantalla crece hacia abajo)
// 	}

// 	// ===== PASO 3: CALCULAR DISTANCIA A LA PARED =====
// 	// Distancia = diferencia entre posición final del rayo y posición del jugador
// 	// Ejemplo: Jugador en (100, 100), rayo toca pared en (103, 104)
// 	//   → dist = √((103-100)² + (104-100)²) = √(9 + 16) = √25 = 5 píxeles
// 	float dist = distance(game->player.ray_x - game->player.x,
// 			game->player.ray_y - game->player.y);
			

// 	// ===== PASO 4: CALCULAR ALTURA DE LA PARED EN PANTALLA =====
// 	// 🔥 FÓRMULA CLAVE DE PROYECCIÓN 3D:
// 	// height = (TAMAÑO_REAL_PARED / distancia) * FACTOR_PERSPECTIVA
// 	//
// 	// ¿Por qué funciona?
// 	// - Cuanto MÁS CERCA está la pared (dist pequeño) → altura GRANDE
// 	// - Cuanto MÁS LEJOS está la pared (dist grande) → altura PEQUEÑA
// 	// - Es una proyección en perspectiva (objetos cercanos parecen más grandes)
// 	//
// 	// Desglose de la fórmula:
// 	// - BLOCK (64): Tamaño real de un bloque en píxeles
// 	// - dist: Distancia calculada al punto de impacto
// 	// - WIDTH/2 (640): Factor de escala para ajustar la altura a la pantalla
// 	//
// 	// Ejemplo 1 (PARED CERCA):
// 	//   dist = 50 píxeles
// 	//   height = (64 / 50) * 640 = 1.28 * 640 = 819 píxeles
// 	//   → Pared MUY ALTA (casi llena la pantalla de 720px)
// 	//
// 	// Ejemplo 2 (PARED LEJOS):
// 	//   dist = 400 píxeles
// 	//   height = (64 / 400) * 640 = 0.16 * 640 = 102 píxeles
// 	//   → Pared PEQUEÑA (solo ocupa el centro)
// 	float height = (BLOCK / dist) * (WIDTH / 2);

// 	// ===== PASO 5: CENTRAR LA PARED VERTICALMENTE =====
// 	// La pared debe dibujarse en el centro vertical de la pantalla
// 	// Si HEIGHT=720 y height=300:
// 	//   start_y = (720 - 300) / 2 = 210
// 	//   end = 210 + 300 = 510
// 	//   → La pared se dibuja de píxel 210 a 510 (centrada)
// 	int start_y = (HEIGHT - height) / 2; // Píxel superior de la pared
// 	int end = start_y + height;          // Píxel inferior de la pared

// 	// ===== PASO 6: DIBUJAR LA COLUMNA VERTICAL =====
// 	// Dibujar una línea vertical en la columna 'i' de la pantalla
// 	// desde start_y hasta end con color azul
// 	while (start_y < end)
// 	{
// 		// put_pixel(i, start_y, 0xFF0000, game);  // Columna i, fila start_y
// 		my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
// 		start_y++;
// 	}
// }

// void cast_ray(t_game *game, float start_x, int i)
// {
//     int max_iterations;
//     int count;
//     float dist;
//     float height;
//     int start_y;
//     int end;
    
//     game->player.cos_angle = cos(start_x);
//     game->player.sin_angle = sin(start_x);
//     game->player.ray_x = game->player.x;
//     game->player.ray_y = game->player.y;
    
//     max_iterations = 1000;
//     count = 0;
    
//     // Loop con límite
//     while (!touch(game->player.ray_x, game->player.ray_y, game) 
//            && count < max_iterations)
//     {
//         game->player.ray_x += game->player.cos_angle;
//         game->player.ray_y -= game->player.sin_angle;
//         count++;
//     }
    
//     // Si no alcanzó pared, no dibujar
//     if (count >= max_iterations)
//         return;
    
//     // Calcular distancia
//     dist = distance(game->player.ray_x - game->player.x,
//                     game->player.ray_y - game->player.y);
    
//     // Protección contra división por cero
//     if (dist < 0.1)
//         dist = 0.1;
    
//     // Calcular altura de la pared
//     height = (BLOCK / dist) * (WIDTH / 2);
    
//     // Limitar altura máxima (evitar overflow)
//     if (height > HEIGHT * 2)
//         height = HEIGHT * 2;
    
//     start_y = (HEIGHT - height) / 2;
//     end = start_y + height;
    
//     //  Dibujar columna
//     while (start_y < end)
//     {
//         if (start_y >= 0 && start_y < HEIGHT)  //  Verificar límites
//             my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
//         start_y++;
//     }
// }

// void cast_ray(t_game *game, float start_x, int i)
// {
//     int max_iterations;
//     int count;
//     float dist;
//     float height;
//     int start_y;
//     int end;
    
//     // 1. Calcular dirección del rayo
//     game->player.cos_angle = cos(start_x);
//     game->player.sin_angle = sin(start_x);
//     game->player.ray_x = game->player.x;
//     game->player.ray_y = game->player.y;
    
//     max_iterations = 1000;
//     count = 0;
    
//     // 2. DDA - Avanzar hasta tocar pared
//     while (!touch(game->player.ray_x, game->player.ray_y, game) 
//            && count < max_iterations)
//     {
//         game->player.ray_x += game->player.cos_angle;
//         game->player.ray_y -= game->player.sin_angle;
//         count++;
//     }
    
//     // 3. Si no alcanzó pared, no dibujar
//     if (count >= max_iterations)
//         return;
    
//     // 4. Calcular distancia euclidiana
//     dist = distance(game->player.ray_x - game->player.x,
//                     game->player.ray_y - game->player.y);
    
//     //  5. CORRECCIÓN FISH-EYE (la clave)
//     // Convertir distancia euclidiana a distancia perpendicular
//     dist = dist * cos(start_x - game->player.angle);
    
//     // 6. Protección contra división por cero
//     if (dist < 0.1)
//         dist = 0.1;
    
//     // 7. Calcular altura de la pared (ahora sin distorsión)
//     height = (BLOCK / dist) * (WIDTH / 2);
    
//     // 8. Limitar altura máxima
//     if (height > HEIGHT * 2)
//         height = HEIGHT * 2;
    
//     // 9. Centrar verticalmente
//     start_y = (HEIGHT - height) / 2;
//     end = start_y + height;
    
//     // 10. Dibujar columna
//     while (start_y < end)
//     {
//         if (start_y >= 0 && start_y < HEIGHT)
//             my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
//         start_y++;
//     }
// }

// RAYCAST SIN BOMBEO
// void cast_ray(t_game *game, float start_x, int i)
// {
//     int max_iterations;
//     int count;
//     float dist;
//     float height;
//     int start_y;
//     int end;
    
//     // 1. Calcular dirección del rayo
//     game->player.cos_angle = cos(start_x);
//     game->player.sin_angle = sin(start_x);
//     game->player.ray_x = game->player.x;
//     game->player.ray_y = game->player.y;
    
//     max_iterations = 1000;
//     count = 0;
    
//     // 2. DDA - Avanzar hasta tocar pared
//     while (!touch(game->player.ray_x, game->player.ray_y, game) 
//            && count < max_iterations)
//     {
//         game->player.ray_x += game->player.cos_angle;
//         game->player.ray_y -= game->player.sin_angle;
//         count++;
//     }
    
//     // 3. Si no alcanzó pared, no dibujar
//     if (count >= max_iterations)
//         return;
    
//     // 4. Calcular distancia euclidiana
//     dist = distance(game->player.ray_x - game->player.x,
//                     game->player.ray_y - game->player.y);
    
//     // 🔥 5. CORRECCIÓN FISH-EYE (la clave)
//     // Convertir distancia euclidiana a distancia perpendicular
//     dist = dist * cos(start_x - game->player.angle);
    
//     // 6. Protección contra división por cero
//     if (dist < 0.1)
//         dist = 0.1;
    
//     // 7. Calcular altura de la pared (ahora sin distorsión)
//     height = (BLOCK / dist) * (WIDTH / 2);
    
//     // 8. Limitar altura máxima
//     if (height > HEIGHT * 2)
//         height = HEIGHT * 2;
    
//     // 9. Centrar verticalmente
//     start_y = (HEIGHT - height) / 2;
//     end = start_y + height;
    
//     // 10. Dibujar columna
//     while (start_y < end)
//     {
//         if (start_y >= 0 && start_y < HEIGHT)
//             my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
//         start_y++;
//     }
// }

void cast_ray(t_game *game, float start_x, int i)
{
    int count;        // 1 (reutilizada para end)
    float dist;       // 2
    float height;     // 3
    int start_y;      // 4
    //  Total: 4 variables
    
    game->player.cos_angle = cos(start_x);
    game->player.sin_angle = sin(start_x);
    game->player.ray_x = game->player.x;
    game->player.ray_y = game->player.y;
    
    count = 0;
    
    while (!touch(game->player.ray_x, game->player.ray_y, game) 
           && count < 1000)
    {
        game->player.ray_x += game->player.cos_angle;
        game->player.ray_y -= game->player.sin_angle;
        count++;
    }
    
    if (count >= 1000)
        return;
    
    dist = distance(game->player.ray_x - game->player.x,
                    game->player.ray_y - game->player.y);
    
    dist = dist * cos(start_x - game->player.angle);
    
    if (dist < 0.1)
        dist = 0.1;
    
    height = (BLOCK / dist) * (WIDTH / 2);
    
    if (height > HEIGHT * 2)
        height = HEIGHT * 2;
    
    start_y = (HEIGHT - height) / 2;
    
    // Reusar count como end (ya no se usa después del while)
    count = start_y + height;
    
    while (start_y < count)
    {
        if (start_y >= 0 && start_y < HEIGHT)
            my_mlx_pixel_put(&game->img, i, start_y, 0x0000FF);
        start_y++;
    }
}


//EXPLICACION AL EFECTO DE PEZ
// start_x: Ángulo del rayo actual
// game->player.angle: Ángulo hacia donde mira el jugador

// start_x - game->player.angle: Diferencia angular
//                                (cuánto se desvía el rayo del centro)

// Ejemplos:
// - Rayo central: start_x = player.angle
//   → start_x - player.angle = 0
//   → cos(0) = 1
//   → dist = dist * 1 (sin cambio)

// - Rayo lateral 30°: start_x = player.angle + 0.52 (30°)
//   → cos(0.52) ≈ 0.866
//   → dist = dist * 0.866 (acorta la distancia percibida)

// - Rayo lateral 60°: start_x = player.angle + 1.05 (60°)
//   → cos(1.05) ≈ 0.5
//   → dist = dist * 0.5 (acorta AÚN MÁS)