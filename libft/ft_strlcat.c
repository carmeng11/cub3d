/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:50:28 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:42 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include "ft_memcpy.c"
#include <stdio.h>
#include "ft_strlen.c"*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;
	size_t	j;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[j] != '\0' && i < (size - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}

/*int	main(void)
{
	char	src[] = "Source";
	char	dst[] = "Destino";
        
        printf("Antes de usar ft_strlcat\n%s\n", dst);
        printf("Después de usar ft_strlcat\n");
        ft_strlcat(dst, src, 9);
        printf("Con la función ft_strlcat:%s\n", dst);
        //strlcat(dst, src, 14);
        //printf("Con la función strlcat:%s\n", dst);
        return (0);
}*/
