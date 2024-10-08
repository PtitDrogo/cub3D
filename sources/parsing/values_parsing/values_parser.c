/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:29:02 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 16:47:07 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		path_check(const char *line, char *data_buffer, int *status);
static int		char_process(const char *line, t_parse *data);
static bool		is_correct_code(const char *line, const char *code);
static bool		is_premap_data_ready(const t_parse *m);

void	values_parser(char **file, t_parse *data)
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
			xpm_check(data);
			if (data->status == 0)
				data->map_start = line;
			return ;
		}
		line++;
	}
	return ;
}

static int	char_process(const char *line, t_parse *data)
{
	if (line[0] == '\0')
		return (1);
	if (is_premap_data_ready(data) == false && ft_strlen(line) < 3)
		return (update_status(ERR_TOO_FEW_CHARS, &data->status), 1);
	if (line[0] == 'N' && is_correct_code(line, "NO"))
		path_check(line, data->no_texts, &data->status);
	else if (line[0] == 'S' && is_correct_code(line, "SO"))
		path_check(line, data->so_texts, &data->status);
	else if (line[0] == 'W' && is_correct_code(line, "WE"))
		path_check(line, data->we_texts, &data->status);
	else if (line[0] == 'E' && is_correct_code(line, "EA"))
		path_check(line, data->ea_texts, &data->status);
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

static bool	is_premap_data_ready(const t_parse *m)
{
	if (!*m->no_texts || !*m->no_texts || !*m->we_texts || !*m->ea_texts)
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
