/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:27:36 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 12:30:34 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_xpm_file(const char *s)
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
	if (s[i] != 'm' || s[i - 1] != 'p' || s[i - 2] != 'x' || s[i - 3] != '.')
		return (false);
	return (true);
}

void	xpm_check(t_parse *data)
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