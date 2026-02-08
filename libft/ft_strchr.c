/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:49:04 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/19 13:49:08 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char) c;
	while (s[i])
	{
		if (*s == cc)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == cc)
	{
		return ((char *)s);
	}
	return (NULL);
}
/*int	main(void)
{
	const char s[] = "here, in the, cursus '\0'";
	int	c;

	c = ',';
	printf("La función devuelve:%s\n", ft_strchr(s, c));
	return (0);
}*/
