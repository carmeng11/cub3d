/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:37:48 by cagomez-          #+#    #+#             */
/*   Updated: 2024/09/24 17:37:53 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stddef.h>*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pos;
	size_t			i;

	i = 0;
	pos = (unsigned char *) s;
	while (i < n)
	{
		pos[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

/*#include <stdio.h>
int	main(void)
{
	unsigned char	ptr[] = "Hello World";
	printf("Antes de usar memset\n%s\n", ptr);
	printf("Después de usar memset\n");
	ft_memset(ptr, '3', 12);
	printf("%s\n", ptr);
	memset(ptr, '3', 12);
	printf("%s", ptr);
}*/