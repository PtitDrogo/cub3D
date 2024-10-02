#include "cub3D.h"

static void		path_check(const char *line, char *data_buffer, int *status);
static int		char_process(const char *line, t_parse_data *data);
static bool		is_correct_code(const char *line, const char *code);
static bool		is_premap_data_ready(const t_parse_data *m);
static bool		is_xpm_file(const char *s);
static void		xpm_check(t_parse_data *data);

void	values_parser(char **file, t_parse_data *data)
{
	size_t	i;
	size_t	line;

	line = 0;
	data->map_start = -1;
	while (file[line])
	{
		i = 0;
		if (data->status != 0)
			return ;
		while (is_white_space(file[line][i]))
			i++;
		if (char_process(&file[line][i], data) == 0)
		{
			data->map_start = line;
			return ;
		}
		line++;
	}
	xpm_check(data);
	return ;
}

static void xpm_check(t_parse_data *data)
{
	if (is_xpm_file(data->NO_texts) == false)
		data->status = ERR_NOT_XPM_FILE;
	if (is_xpm_file(data->SO_texts) == false)
		data->status = ERR_NOT_XPM_FILE;
	if (is_xpm_file(data->WE_texts) == false)
		data->status = ERR_NOT_XPM_FILE;
	if (is_xpm_file(data->EA_texts) == false)
		data->status = ERR_NOT_XPM_FILE;
	return ;
}

static int	char_process(const char *line, t_parse_data *data)
{
	if (line[0] == '\0')
		return (1);
	if (ft_strlen(line) < 3)
		return (update_status(ERR_TOO_FEW_CHARS, &data->status), 1);
	if (line[0] == 'N' && is_correct_code(line, "NO"))
		path_check(line, data->NO_texts, &data->status);
	else if (line[0] == 'S' && is_correct_code(line, "SO"))
		path_check(line, data->SO_texts, &data->status);
	else if (line[0] == 'W' && is_correct_code(line, "WE"))
		path_check(line, data->WE_texts, &data->status);
	else if (line[0] == 'E' && is_correct_code(line, "EA"))
		path_check(line, data->EA_texts, &data->status);
	else if (line[0] == 'C' && is_correct_code(line, "C"))
		rgb_parsing(line, &data->ceiling_colors, &data->status);
	else if (line[0] == 'F' && is_correct_code(line, "F"))
		rgb_parsing(line, &data->floor_colors, &data->status);
	else if (is_map_char(line[0]) == true)
	{
		if (is_premap_data_ready(data) == false)
			return (update_status(ERR_MAP_TOO_SOON, &data->status), 1);
		return (0);
	}
	else
		return (update_status(ERR_INVALID_CHAR, &data->status), 1);
	return (1);
}

static void	path_check(const char *line, char *data_buffer, int *status)
{
	size_t	i;
	size_t	path_len;

	i = 0;
	if (data_buffer[0] != '\0')
		return (update_status(ERR_DEFINED_TWICE, status));
	skip_word(line, &i);
	path_len = strlen_until_whitespace(&line[i]);
	if (path_len + 1 > PATH_MAX)
		return (update_status(ERR_PATH_TOO_BIG, status));
	ft_strlcpy(data_buffer, &line[i], path_len + 1);
	i += path_len;
	while (is_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (update_status(ERR_TOO_MANY_PATHS, status));
}

static bool	is_premap_data_ready(const t_parse_data *m)
{
	if (!*m->NO_texts || !*m->NO_texts || !*m->WE_texts || !*m->EA_texts)
		return (false);
	if (m->floor_colors.is_defined == false)
		return (false);
	if (m->ceiling_colors.is_defined == false)
		return (false);
	return (true);
}

static bool	is_correct_code(const char *line, const char *code)
{
	int	i;

	i = 0;
	if (ft_strncmp(line, code, ft_strlen(code)) == 0)
	{
		while (line[i] == code[i])
			i++;
		return (is_white_space(line[i]));
	}
	return (false);
}

static bool is_xpm_file(const char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 5)
	{	
		return (false);
	}
	while (s[i])
		i++;
	i--;
	printf("i = %i char is %c\n", i, s[i]);
	if (s[i] != 'm' || s[i - 1] != 'p' || s[i - 2] != 'x' || s[i - 3] != '.')
	{	
		return (false);
	}
	return (true);
}
