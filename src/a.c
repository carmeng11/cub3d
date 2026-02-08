#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	*ft_str(char *filename)
{
	size_t	len;
	char	*extension;

	len = strlen(filename);// map.cub len = 7
	while (len > 0)
	{
		if (filename[len] == '.')
		{
			extension = &filename[len];
			return (extension);
		}
		len--;
	}
	if (!extension || strncmp(extension, ".cub", 5) != 0)
		return NULL;
}
	
int	main()
{
	char	*filename = "map.cuub";
	printf("%s\n", ft_str(filename));
	return (0);
}