#include "../includes/parsing.h"

void	print_error_msg(int err_code)
{
	if (err_code == TOO_MANY_PLYR_ERR)
		printf("Too many players were found !\n");
	if (err_code == ZERO_PLAYER_ERR)
		printf("No players were found !\n");
	if (err_code == INVALID_CHAR_ERR)
		printf("An invalid char was found !\n");
}

bool	contains_invalid_char(char *str, int *cpt)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (is_allowed_char(str[i]))
		{
			if (is_direction_c(str[i]))
				(*cpt) += 1;
			i++;
		}
		else
		{
			// printf("Sorry ! (%c)->int %d is invalid !\n", str[i], str[i]); //remove
			return (true);
		}
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
		// printf("\nAnalysing (%s) ...\n\n", m_map[i]);
		if (contains_invalid_char(m_map[i], &cpt))
			return (3);
		if (cpt > 1)
			return (1);
		i++;
	}
	if (cpt == 0)
		return (2);
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
		current = ft_len(map[i]);//change to ft_strlen()
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
	while (y < height - 1)
	{
		if ((map[y][0] == '0') ||
				(map[y][length - 1] == '0'))
			return (1);
		else
			y++;
	}
	while (x < length - 2)
	{
		if ((map[0][x] == '0') ||
				(map[height - 1][x] == '0'))
			return (1);
		else
			x++;
	}
	return (0);
}

int		unclosed_map(char **map, int height, int length)
{
	if(check_outer_line(map, height, length))
		return (4);
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
		len = ft_len(map[i]);
		if (len < max_len)
			map[i] = add_spaces_to_str(map[i], max_len, len);		
		i++;
	}
	print_map(map); //debug
}

bool	is_map_valid(char **m_map)
{
	int	map_height;
	int	map_length;
	int	err_code;

	get_map_height(m_map, &map_height, &map_length);
	expand_map(m_map, map_length);
	err_code = invalid_player(m_map);
	if (!err_code)
		err_code = unclosed_map(m_map, map_height, map_length);
	if (err_code) // final check
	{
		print_error_msg(err_code);
		printf("Leaving ...\n\n\n");
		return (false);
	}
	printf("Everything is valid ! Leaving ...\n");
	return (false); //only for debug, to change back to true
}
