#include "cub3D.h"

void	print_map(char **map)
{
	int	j;

	j = 0;
	printf("\n");
	for(int i = 0; map[i]; i++)
	{
		ft_printf(" %d  |%s|\n", j++, map[i]);
	}
	j = 0;
	printf("\n\n");
}

void	print_map_current(char **map, int x, int y)
{
	char	**cpy;
	int		height;
	int		length;
	int		i;

	i = 0;
	get_map_height(map, &height, &length);
	cpy = malloc(sizeof(char **) * (height * sizeof(char *)) + 1);
	while(map[i])
	{
		cpy[i] = ft_strdup(map[i]);
		i++;
	}
	cpy[i] = NULL;
	if (cpy[y][x] == '1')
		cpy[y][x] = 'X';
	else
		cpy[y][x] = '*';
	printf("Cheking pos for x=%d and y=%d : \n", x, y);
	print_map(cpy);
	ft_free_array((void *)cpy);
}

bool	is_direction_c(char c)
{
	return (c == 'W' || c == 'E'
		|| c == 'N' || c == 'S');
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'D'
		|| is_direction_c(c)
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' '
		|| c == '\n');
}
