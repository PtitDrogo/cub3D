#include "cub3D.h"

bool	contains_invalid_char(char *str, int *cpt)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_map_char(str[i]))
		{
			if (is_direction_c(str[i]))
				(*cpt) += 1;
			i++;
		}
		else
			return (true);
	}
	return (false);
}

int	invalid_player(char **m_map)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;

	while (m_map[i])
	{
		if (contains_invalid_char(m_map[i], &cpt))
			return (ERR_INVALID_CHAR_MAP);
		if (cpt > 1)
			return (ERR_TOO_MANY_PLYR);
		i++;
	}
	if (cpt == 0)
		return (ERR_ZERO_PLAYER);
	return (0);
}

void	get_map_height(char **map, int *height, int *length)
{
	int	i;
	int	longest;
	int	current;

	i = 0;
	longest = 0;
	while(map[i])
		i++;
	*height = i;
	i = 0;
	while(map[i])
	{
		current = ft_strlen(map[i]);
		if (current > longest) 
			longest = current;
		i++;
	}
	*length = longest;
}

int	check_outer_line(char **map, int height, int length)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < height)
	{
		// printf("checking map[%d][0] AND ",y);
		// printf("checking map[%d][%d]\n", y, length - 1);
		if ((map[y][0] == '0') || (map[y][0] == 'E') ||
				(map[y][length - 1] == '0') ||
				(map[y][length - 1] == 'E'))
			return (1);
		else
			y++;
	}
	// printf("\ndone checking vertically ....\n\n");
	while (x < length - 1)
	{
		// printf(" 2 :checking map[0][%d] AND ",x);
		// printf("checking map[%d][%d]\n", height - 1, x);
		if ((map[0][x] == '0') || (map[0][x] == 'E') ||
				(map[height - 1][x] == '0') ||
				(map[height - 1][x] == 'E'))
			return (1);
		else
			x++;
	}
	return (0);
}

bool	invalid_neighbour(char **map, int x, int y)
{
	if (is_white_space(map[y][x - 1]))
		return (true);
	if (is_white_space(map[y][x + 1]))
		return (true);
	if (is_white_space(map[y - 1][x]))
		return (true);
	if (is_white_space(map[y + 1][x]))
		return (true);
	return (false);
}

int		check_inner_map(char **map, int height, int length)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < height - 1)
	{
		x = 1;
		// printf("|");
		while (x < length - 1)
		{
			// printf("%c", map[y][x]);
			if (map[y][x] == '0' || is_direction_c(map[y][x]))
			{
				if(invalid_neighbour(map, x , y))
					return (1);
			}
			x++;
		}
		// printf("|\n");
		y++;
	}
	return (0);
}

int		unclosed_map(char **map, int height, int length)
{
	if(check_outer_line(map, height, length))
		return (ERR_INVALID_CHAR_MAP);
	if (check_inner_map(map, height, length))
		return (ERR_INVALID_CHAR_MAP);
	return (0);
}

char	*add_spaces_to_str(char *line, int max_len, int len)
{
	char *new_line;

	new_line = ft_calloc(sizeof(char), max_len + 1);
	if (!new_line)
		return (NULL);
	ft_memset(new_line, ' ', max_len);
	ft_memcpy(new_line, line, len);
	free(line);
	return (new_line);
}

void	expand_map(char **map, int max_len)
{
	int		len;
	int		i;

	i = 0;
	while(map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_len)
			map[i] = add_spaces_to_str(map[i], max_len, len);		
		i++;
	}
	printf("the map that map parser sees is : \n");
	print_map(map); //debug
}

bool	is_map_valid(t_info *w, char **m_map)
{
	int	m_height;
	int	m_length;
	int	err_code;

	get_map_height(m_map, &m_height, &m_length);
	w->map_heigth = m_height;
	w->map_lenght = m_length;
	expand_map(m_map, m_length);
	err_code = invalid_player(m_map);
	if (!err_code)
		err_code = unclosed_map(m_map, m_height, m_length);
	if (err_code)
	{
		print_error_msg(err_code);
		printf("Leaving errcode was %i...\n\n\n", err_code); //debug
		return (false);
	}
	printf("Everything is valid ! Leaving ...\n");
	printf("\n\n\n############################################################################\n\n\n");
	return (true);
}
