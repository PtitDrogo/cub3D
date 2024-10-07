/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:55:28 by lchapard          #+#    #+#             */
/*   Updated: 2024/10/07 13:55:29 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*add_spaces_to_str(char *line, int max_len, int len)
{
	char	*new_line;

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
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_len)
			map[i] = add_spaces_to_str(map[i], max_len, len);
		i++;
	}
}

void	get_map_height(char **map, int *height, int *length)
{
	int	i;
	int	longest;
	int	current;

	i = 0;
	longest = 0;
	while (map[i])
		i++;
	*height = i;
	i = 0;
	while (map[i])
	{
		current = ft_strlen(map[i]);
		if (current > longest)
			longest = current;
		i++;
	}
	*length = longest;
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
