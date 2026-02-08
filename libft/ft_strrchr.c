/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmen <carmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:15:27 by cagomez-          #+#    #+#             */
/*   Updated: 2026/01/13 18:54:53 by carmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
// #include <stddef.h>
// #include "ft_strlen.c"
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			cc;
	int				len;

	len = ft_strlen(s);
	cc = (char)c;
	while (len > 0)
	{
		if (s[len] == cc)
			return ((char *)&s[len]);
		len--;
	}
	if (s[len] == cc)
		return ((char *)&s[len]);
	return (NULL);
}

/*char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;
	char			*result;

	result = NULL;
	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			result = (char *)&s[i];
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (result);
}*/

// int	main(void)
// {
// 	const char s[] = "me llamo carmen";
// 	int	c;
	
// 	c = 'c';
// 	printf("La función devuelve:%s\n", ft_strrchr(s, c));
// 	printf("hola, mi nombre es %s y tengo %d años\n", "laura", 23);
// 	return (0);
// }
