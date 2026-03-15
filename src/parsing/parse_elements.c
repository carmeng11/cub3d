/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 18:38:59 by cagomez-          #+#    #+#             */
/*   Updated: 2026/03/15 18:47:32 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_line(char *line, t_game *game)
{
	int i;
	
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.north));
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.south));
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.west));
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (parse_texture_line(&line[i + 3], &game->textures.east));
	
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (parse_color_line(&line[i + 2], &game->floor));
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (parse_color_line(&line[i + 2], &game->ceiling));
	
	
	return (0);
}