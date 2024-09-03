/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:01:49 by tfreydie          #+#    #+#             */
/*   Updated: 2024/09/03 16:57:34 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_and_null(char *line)
{
	free(line);
	return (NULL);
}

char	*final_check(char *line)
{
	if (line[0])
		return (line);
	return (free_and_null(line));
}
