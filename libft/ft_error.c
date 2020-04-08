#include "libft.h"

void	ft_error(char *fuckup)
{
	int i;

	i = 0;
	while (fuckup[i] != '\0')
	{
		write(2, &fuckup[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit (-1);
}