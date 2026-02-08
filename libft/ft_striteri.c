/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:35:45 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/11 19:35:50 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <stddef.h>
#include "ft_strlen.c"*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*void    ft_touper(unsigned int i, char *c)
{
	//int	i;
	i = 0;
	while (c[i])
	{
		if (c[i] >= 'a' && c[i] <= 'z')
        		c[i] = c[i] - 32;
		i++;
	}
}

int main(void)
{
    char    word[] = "hola mundo";

    printf("Antes:%s\n", word);
    ft_striteri(word, ft_touper);
    printf("Después:%s\n", word);
    return (0);
}*/
