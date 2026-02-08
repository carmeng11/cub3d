/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:02:47 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/04 20:02:54 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>
#include <stdio.h>
#include <string.h>*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destp;
	unsigned char	*srcp;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	destp = (unsigned char *) dest;
	srcp = (unsigned char *) src;
	i = 0;
	if (destp > srcp)
	{
		while (n-- > 0)
			destp[n] = srcp[n];
	}
	else
	{
		while (i < n)
		{
			destp[i] = srcp[i];
			i++;
		}
	}
	return (dest);
}

/*int main(void)
{
	unsigned char	dest[] = "Hellohow";
	unsigned char	src[] = "hola";
	unsigned char	src2[] = "hi";
	size_t	n;

	n = 4;
	printf("Antes de usar ft_memmove\n%s\n", dest);
	ft_memmove(dest, src, n);
	printf("Con la función ft_memmove:%s\n", dest);
	memmove(dest, src2, 2);
	printf("Con la función memmove:%s\n", dest);
	return (0);
}*/
