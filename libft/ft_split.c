/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:53:44 by cagomez-          #+#    #+#             */
/*   Updated: 2024/10/17 18:53:47 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>
#include "ft_strlen.c"
#include "ft_calloc.c"
#include "ft_substr.c"
#include "ft_strdup.c"*/

static int	count_words(const char *str, char c)
{
	int	x;
	int	count;
	int	i;

	x = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && x == 0)
		{
			count++;
			x = 1;
		}
		else if (str[i] == c && x == 1)
			x = 0;
		i++;
	}
	return (count);
}

static int	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	write_str(char **res, char *str, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] != c && str[i + j])
				j++;
			res[count] = ft_substr(str, i, j);
			if (res[count] == NULL)
				return (free_str(res));
			i = i + j;
			count++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**res;

	if (!s)
		return (NULL);
	count = count_words((char *)s, c);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!write_str(res, (char *)s, c))
		return (NULL);
	return (res);
}

/*int main()
{
	char	s[] = "////hi /worl/// bye/ how/are/you";
	char	c;
	char	**res;

	c = '/';
	int i = 0;
	res = ft_split(s, c);
	if (res == NULL)
	{
		printf("Error.\n");
		return (1);
	}
	for 
		(int i = 0; 
		res[i] != NULL; 
		i++)
	{
		printf("Palabra %d: %s\n", i + 1, res[i]);
		free(res[i]);
	}
	free(res);
	return (0);	
}*/