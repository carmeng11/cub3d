/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:06:49 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/07 18:06:54 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>
#include "ft_memcpy.c"
#include "ft_strlen.c"*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/*int	main(void)
{
	unsigned int	i;
	char	src [] = "Hihowareyou";
	char	dst[] = "Hola";
	size_t	dstsize;
	
	i = 0;
	dstsize = 5;
	//printf("Antes de la función el origen y el destino es: %s y %s", src, dst);
	printf("\nEl tamaño del buffer de destino es: %zu", dstsize);
	ft_strlcpy(dst, src, dstsize);
	printf("\nEl texto de destino después de la función es: %s\n", dst);
	printf("Tamaño de la cadena de origen %zu", ft_strlcpy(dst, src, dstsize));
	return (0);
}*/
