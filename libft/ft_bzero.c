/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:38:20 by cagomez-          #+#    #+#             */
/*   Updated: 2024/09/24 17:43:39 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>
#include <strings.h>*/

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*pos;
	size_t			i;

	i = 0;
	pos = (unsigned char *) s;
	while (i < n)
	{
		pos[i] = 0;
		i++;
	}
	return (s);
}

/*#include <stdio.h>
int	main(void)
{
	unsigned char s[] = "Hello world";
	size_t	i;
	size_t	n;

	i = 0;
	n = 5;
	printf("El texto antes de la función: %s\n", s);
	printf("El texto después de la función: ");
	ft_bzero(s, n);
	printf("Con ft_bzero: %s\n", s);
	bzero(s, n);
	printf("Con bzero: %s\n", s);
	while (i < n)
	{
		printf("%d", s[i]);
		i++;
	}
	return (0);
}*/