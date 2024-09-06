#include "parsing.h"

static int 	get_rgb_value(const char buffer[4], int *status);
static int	update_rgb_data(t_rgb *rgb, int num, const char buffer[4], int *status);
static void get_to_n_fill_buffer(char buffer[4], const char *line, size_t *i);

void	rgb_parsing(const char *line, t_rgb *rgb, int *status)
{
	size_t	i;
	size_t	num;
	char	buffer[4];

	num = 0;
	i = 0;
	if (rgb->is_defined == true)
		return (update_status(ERR_DEFINED_TWICE, status));
	skip_word(line, &i);
	while (num < 3)	
	{
		ft_bzero(buffer, 4);
		get_to_n_fill_buffer(buffer, line, &i);
		if (num == 2)
		{
			if (line[i] != '\0')
			{	
				printf("problematic char is %c|", buffer[i]);
				return (update_status(ERR_RGB_WRONG_FORMAT, status));
			}
		}
		else if (line[i++] != ',')
		{	
			printf("problematic char is %c|", buffer[i - 1]);
			return (update_status(ERR_RGB_WRONG_FORMAT, status));
		}
		if (update_rgb_data(rgb, num, buffer, status) == 1)
			return ;
		num++;
	}
	rgb->is_defined = true;
}

//Gets rgb value, returns -1 if an error was encountered
static int 	get_rgb_value(const char buffer[4], int *status)
{
	size_t	i;
	int     rgb_value;

	i = 0;
	printf("content of rgb is : %s|\n", buffer);
	while (buffer[i] && i < ft_strlen(buffer) )
	{
		if (ft_isdigit(buffer[i]) == false)
		{	
			printf("problematic char is %c|", buffer[i]);
			return (update_status(ERR_RGB_NaN, status), -1);
		}
		i++;
	}
	rgb_value = ft_atoi(buffer);
	return (rgb_value);
}

//update the rgb struct and returns 0, returns 1 if it couldn't
static int update_rgb_data(t_rgb *rgb, int num, const char buffer[4], int *status)
{
	int		rgb_value;
	
	rgb_value = get_rgb_value(buffer, status);
	if (rgb_value == -1)
		return (1);
	if (num == 0)
		rgb->r = rgb_value;
	else if (num == 1)
		rgb->g = rgb_value;
	else if (num == 2)
		rgb->b = rgb_value;
	return (0);
}

static void get_to_n_fill_buffer(char buffer[4], const char *line, size_t *i)
{
	size_t	j;
	size_t	index;

	index = *i;
	ft_bzero(buffer, 4);
	j = 0;
	while (is_white_space(line[index]) == true)
		index++;
	while (ft_isdigit(line[index]) && j < 3)
		buffer[j++] = line[index++];
	while (is_white_space(line[index]) == true)
		index++;
	*i = index;
	return ;
}
