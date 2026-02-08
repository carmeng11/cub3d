/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:38 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/10 19:41:41 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <stddef.h>
#include "ft_strlen.c"
#include "ft_putnbr_fd.c"*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*char	ft_touper(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	ft_putnbr_fd (i, 1);
	return (c);
}

int	main(void)
{
	char s[] = "hello world";
	char *new_string = ft_strmapi(s, ft_touper);

	printf("Original string: %s\n", s);
	printf("Modified string: %s\n", new_string);
	free(new_string);
	return (0);
}*/
