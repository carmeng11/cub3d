# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/02 12:00:00 by cagomez-          #+#    #+#              #
#    Updated: 2026/02/06 18:32:05 by cagomez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I./includes -I./libft 
LIBS        = -L$(LIBFT_DIR) -lft
RM			= rm -f

# Directorios
SRC_DIR		= src
OBJ_DIR		= obj
MLX_DIR		= minilibx-linux
LIBFT_DIR	= libft

# Librerías
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# Archivos fuente
SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/player.c \
			  $(SRC_DIR)/pixel_draw.c \
			  $(SRC_DIR)/map_draw.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/events.c \
			  $(SRC_DIR)/parsing/parse_file.c \
			  $(SRC_DIR)/parsing/parse_textures.c \
			  $(SRC_DIR)/parsing/parse_colors.c \
			  $(SRC_DIR)/utils/error.c \
			  $(SRC_DIR)/utils/get_next_line.c \

# Objetos
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colores
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Reglas
all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(GREEN)Compilando libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREEN)Compilando MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@
	@echo "$(GREEN)Compilado: $<$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) creado exitosamente!$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Objetos eliminados$(RESET)"
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(RED)$(NAME) eliminado$(RESET)"
	@make -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re