/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:42:27 by cagomez-          #+#    #+#             */
/*   Updated: 2024/09/28 11:42:40 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>
#include <stdio.h>
#include <string.h>*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destp;
	unsigned char	*srcp;
	size_t			i;

	i = 0;
	destp = (unsigned char *) dest;
	srcp = (unsigned char *) src;
	if ((dest == NULL && src == NULL) && n > 0)
		return (NULL);
	while (i < n)
	{
		destp[i] = srcp[i];
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	unsigned char	dest[] = "hola";
	unsigned char	src[] = "Hellohow";
	size_t	n;

	n = 3;
	printf("Antes de usar memcpy\n%s\n", dest);
	printf("Después de usar memcpy\n");
	ft_memcpy(dest, src, n);
	printf("Con la función ft_memcpy:%s\n", dest);
	memcpy(dest, src, n);
	printf("Con la función memcpy:%s\n", dest);
	return (0);
}*/