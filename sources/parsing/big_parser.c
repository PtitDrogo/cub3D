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
	//check if a map starts;
	return (0);
}

static int	char_process(char *line, t_parse_data *data)
{
	//Im cringing I have to do this;

	//Texture check (Always checking ft_strlen is cringe i know ill fix it later)
	if (is_map_char(line[0]) == true)
	{
		//check if all maps are set
		return (update_status(ERR_DEFINED_TWICE, &data->status), 1);
		return (0);
	}
	if (line[0] == 'N' && ft_strlen(line) >= 3) 
	{	
		if (ft_strncmp(line, "NO ", ft_strlen("NO ")) == 0)
			texture_path_check(line, data->NO_texts, &data->status);
	}
	else if (line[0] == 'S' && ft_strlen(line) >= 3) 
	{	
		if (ft_strncmp(line, "SO ", ft_strlen("SO ")) == 0)
			texture_path_check(line, data->SO_texts, &data->status);
	}
	else if (line[0] == 'W' && ft_strlen(line) >= 3) 
	{	
		if (ft_strncmp(line, "WE ", ft_strlen("WE ")) == 0)
			texture_path_check(line, data->WE_texts, &data->status);
	}
	else if (line[0] == 'E' && ft_strlen(line) >= 3) 
	{	
		if (ft_strncmp(line, "EA ", ft_strlen("EA ")) == 0)
			texture_path_check(line, data->EA_texts, &data->status);
	}
	// texture check end

	//RGB VALUE CHECK
	else if (line[0] == 'C' && ft_strlen(line) >= 3)
	{
		if (ft_strncmp(line, "C ", ft_strlen("C ")) == 0)
			rgb_parsing(line, data->ceiling_colors, &data->status);
	}
	else if (line[0] == 'F' && ft_strlen(line) >= 3)
	{
		if (ft_strncmp(line, "F ", ft_strlen("F ")) == 0)
			rgb_parsing(line, data->floor_colors, &data->status);
	}
	//RGB VALUE CHECK END

	//if I see a map char, check if everything is set;

	//else, any other char is an error;

	return (0);

}

static void	texture_path_check(char *line, char *data_buffer, int *status)
{
	size_t i;
	size_t path_len;
	
	i = 0;
	if (data_buffer != NULL)
		return (update_status(ERR_DEFINED_TWICE, status));
	while (is_white_space(line[i]))
			i++;
	path_len = strlen_until_whitespace(&line[i]);
	if (path_len > PATH_MAX)
		return (update_status(ERR_PATH_TOO_BIG, status));
	ft_strlcpy(data_buffer, &line[i], path_len); //Copying into the data buffer;
	// printf("Just did a copy on line \"%s\"!\n", line);
	while (is_white_space(line[i]))
			i++;
	if (line[i] != '\0')
		return (update_status(ERR_TOO_MANY_PATHS, status));
}

static bool is_premap_data_ready(const t_parse_data *m)
{
	if (!m->NO_texts || !m->NO_texts || !m->WE_texts || !m->EA_texts)
		return (false);
	if (m->floor_colors[DEF_STATUS] == 0)
		return (false);
	if (m->ceiling_colors[DEF_STATUS] == 0)
		return (false);
}

