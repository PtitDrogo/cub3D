#include "parsing.h"

static int get_rgb_value(const char buffer[4], int *status);

void	rgb_parsing(char *line, unsigned char colors[4], int *status)
{
	char	buffer[4];
	int		color;
	size_t	i;
	size_t	n_color;

	n_color = 0;
	i = 0;
	if (colors[DEF_STATUS] == 1)
		return (update_status(ERR_DEFINED_TWICE, status));
	while (n_color++ < 3)
	{
		ft_bzero(buffer, 4);
		while (line[i++] && line[i] != ',' && i < 3)
			buffer[i] = line[i];
		if ((line[i] != ',' && n_color != 2) || (n_color == 2 && line[i] != '\0'))
			return (update_status(ERR_RGB_WRONG_FORMAT, status));
		color = get_rgb_value(buffer, status);
		if (color == -1)
			return ;
		colors[n_color] = (unsigned char)color;
		if (n_color == 2)
			colors[DEF_STATUS] = 1;
	}
}

//Gets rgb value, returns -1 if an error was encountered
int get_rgb_value(const char buffer[4], int *status)
{
	size_t	i;
	int     rgb_value;

	i = 0;
	while (i < 3)
	{
		if (ft_isdigit(buffer[i]) == false)
			return (update_status(ERR_RGB_NaN, status), false);
		i++;
	}
	rgb_value = ft_atoi(buffer);
	if (rgb_value > 255)
	{	
		update_status(ERR_RGB_INVALID_VALUE, status);
		return (-1);
	}
	return (rgb_value);
}
