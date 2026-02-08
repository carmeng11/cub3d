#include "cub3d.h"
#include <unistd.h>

void	print_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
}
