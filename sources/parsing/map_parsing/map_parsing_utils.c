/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:31:29 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 12:25:15 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_direction_c(char c)
{
	return (c == 'W' || c == 'E'
		|| c == 'N' || c == 'S');
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'D'
		|| is_direction_c(c)
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' '
		|| c == '\n' || c == '	');
}