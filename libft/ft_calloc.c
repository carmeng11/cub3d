/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:12:28 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/07 18:12:34 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <stdio.h>*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	while (i < nmemb * size)
		str[i++] = 0;
	return (str);
}

/*int	main(void)
{
	char	str[] = "    ";

	printf("Después de calloc la cadena es %p: ",ft_calloc(5, 1));
	ft_calloc(5, 1);
	printf("%s:", str);
	printf("El tamaño reservado es:%ld", sizeof(str));
	return (0);
}*/
