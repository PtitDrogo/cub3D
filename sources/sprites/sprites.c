/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:32:32 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:04:38 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_addr_sprites(t_image *image)
{
	image->pix_addr = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel,
			&image->size_line, &image->endian);
	if (!image->pix_addr)
		return (1);
	return (0);
}

void	load_all_address_sprites(t_info *w)
{
	int		i;
	int		end;
	int		err;
	t_image	*ptr;

	err = 0;
	i = 0;
	ptr = (t_image *)&w->assets;
	end = sizeof(t_assets) / sizeof(t_image);
	while (i < end)
	{
		err += load_addr_sprites(&ptr[i]);
		i++;
	}
	if (err)
	{
		ft_printf2("Error!\nCouldn't set sprite adress!\n");
		free_window(w);
		exit (EXIT_FAILURE);
	}
	return ;
}
