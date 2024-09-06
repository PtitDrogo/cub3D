#include "cub3D.h"

void	print_map(char **map) //only for debug, to delete
{
	int	i;

	i = 0;
	printf("\n\n");
	for(int i = 0; map[i]; i++)
		ft_printf("|%s|\n", map[i]);
	printf("\n\n");
}

bool	is_direction_c(char c)
{
	return (c == 'W' || c == 'E'
		|| c == 'N' || c == 'S');
}
//I removed tab from allowed char 
bool	is_map_char(char c)
{	
	return (c == '0' || c == '1'
		|| is_direction_c(c)
		|| c == '\v'|| c == '\f' 
		|| c == '\r' || c == ' ' 
		|| c == '\n');
}
