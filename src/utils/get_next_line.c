# include "cub3d.h"

// #ifndef GET_NEXT_LINE_H
// # define GET_NEXT_LINE_H

// # include <stdio.h>
// # include <fcntl.h>
// # include <stdlib.h>
// # include <unistd.h>

// # ifndef BUFFER_SIZE
// # define BUFFER_SIZE 10

// # endif

// char	*get_next_line(int fd);

// #endif

char	*ft_strdup_gnl(char *str)
{
	int	i;
	char	*dst;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	int	i;
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read;
	static int	buffer_pos;
	char	line[70000];

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

// int	main()
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("map.cub", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
