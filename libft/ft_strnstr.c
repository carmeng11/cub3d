/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:51:26 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/03 17:51:30 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *) big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

/*int	main(void)
{
	char	big [] = "Hello Wor World";
	char	little [] = "World";
	size_t	len;
	//char	*result = ft_strnstr(big, little, len);

	len = 15;	
	printf("La subcadena encontrada es:%s\n", ft_strnstr(big, little, len));
	return (0);
}*/
