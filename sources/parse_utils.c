#include "../includes/parsing.h"

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
	if (c == 'W' || c == 'E'
		|| c == 'N' || c == 'S')
	{
		return (true);
	}
	else
		return (false);
}

bool	is_allowed_char(char c)
{
	if (c == '0' || c == '1' 
		|| c == 'W' || c == 'E'
		|| c == 'N' || c == 'S'
		|| c == '\t' || c == '\v'
		|| c == '\f' || c == '\r'
		|| c == ' ' || c == '\n')
	{
		return (true);
	}
	else
		return (false);
}