#include "parsing.h"


static void		texture_path_check(char *line, char *data_buffer, int *status);
static int		char_process(char *line, t_parse_data *data);

int	big_parser(char **file, t_parse_data *data)
{
	int i;
	int line;
	
	i = 0;
	line = 0;
	while (file[line])
	{
		while (is_white_space(file[line][i]))
			i++;
		char_process(&file[line][i], data);
		line++;
	}
	 //silence compiler
	return (0);
}

static int	char_process(char *line, t_parse_data *data)
{
	size_t i;

	i = 0;
	if (line[0] == 'N' && ft_strlen(&line[0]) >= 3) 
		if (ft_strncmp(line, "NO ", ft_strlen("NO ")) == 0)
			texture_path_check(line, data->NO_textures, &data->status);
	else if (line[0] == 'S' && ft_strlen(&line[0]) >= 3) 
		if (ft_strncmp(line, "SO ", ft_strlen("SO ")) == 0)
			texture_path_check(line, data->SO_textures, &data->status);
	else if (line[0] == 'N' && ft_strlen(&line[0]) >= 3) 
		if (ft_strncmp(line, "WE ", ft_strlen("WE ")) == 0)
			texture_path_check(line, data->WE_textures, &data->status);
	else if (line[0] == 'N' && ft_strlen(&line[0]) >= 3) 
		if (ft_strncmp(line, "EA ", ft_strlen("EA ")) == 0)
			texture_path_check(line, data->EA_textures, &data->status);
	return (0);

}

void	texture_path_check(char *line, char *data_buffer, int *status)
{
	size_t i;
	size_t path_len;
	
	i = 0;
	while (is_white_space(line[i]))
			i++;
	path_len = strlen_until_whitespace(&line[i]);
	if (path_len > PATH_MAX)
	{
		status = ERR_PATH_TOO_BIG;
		return ; 
	}
	else
		ft_strlcpy(data_buffer, &line[i], path_len); //Copying into the data buffer;
	while (is_white_space(line[i]))
			i++;
	if (line[i] != '\0')
	{
		status = ERR_TOO_MANY_PATHS;
		return ;
	}


}



// int	rgb_parsing(char *line, t_parse_data *data)
// {

// }

// int	texture_parsing(char *line, t_parse_data *data)
// {

// }

// int map_parsing(char **map, t_parse_data *data)
// {

// }