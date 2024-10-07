/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:37:55 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:12:00 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	did_load_cloud_fail(t_info *w);
static bool	did_load_boom_fail(t_info *w);

int	load_bonus_boom(t_info *w)
{
	w->assets.b1.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom1.xpm", &w->assets.b1.width, &w->assets.b1.height);
	w->assets.b2.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom2.xpm", &w->assets.b2.width, &w->assets.b2.height);
	w->assets.b3.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom3.xpm", &w->assets.b3.width, &w->assets.b3.height);
	w->assets.b4.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom4.xpm", &w->assets.b4.width, &w->assets.b4.height);
	w->assets.b5.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom5.xpm", &w->assets.b5.width, &w->assets.b5.height);
	w->assets.b6.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom6.xpm", &w->assets.b6.width, &w->assets.b6.height);
	w->assets.b7.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom7.xpm", &w->assets.b7.width, &w->assets.b7.height);
	w->assets.b8.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom8.xpm", &w->assets.b8.width, &w->assets.b8.height);
	w->assets.b9.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom9.xpm", &w->assets.b9.width, &w->assets.b9.height);
	w->assets.b10.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/boom10.xpm",
			&w->assets.b10.width, &w->assets.b10.height);
	if (did_load_boom_fail(w) == true)
		return (1);
	return (0);
}

int	load_bonus_cloud(t_info *w)
{
	w->assets.c1.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud1.xpm", &w->assets.c1.width, &w->assets.c1.height);
	w->assets.c2.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud2.xpm", &w->assets.c2.width, &w->assets.c2.height);
	w->assets.c3.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud3.xpm", &w->assets.c3.width, &w->assets.c3.height);
	w->assets.c4.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud4.xpm", &w->assets.c4.width, &w->assets.c4.height);
	w->assets.c5.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud5.xpm", &w->assets.c5.width, &w->assets.c5.height);
	w->assets.c6.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud6.xpm", &w->assets.c6.width, &w->assets.c6.height);
	w->assets.c7.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud7.xpm", &w->assets.c7.width, &w->assets.c7.height);
	w->assets.c8.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud8.xpm", &w->assets.c8.width, &w->assets.c8.height);
	w->assets.c9.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud9.xpm", &w->assets.c9.width, &w->assets.c9.height);
	w->assets.c10.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cloud10.xpm",
			&w->assets.c10.width, &w->assets.c10.height);
	if (did_load_cloud_fail(w) == true)
		return (1);
	return (0);
}

int	load_sprites(t_info *w, t_parse *d, int err)
{
	w->assets.n_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->NO_texts, &w->assets.n_wall.height, &w->assets.n_wall.width);
	w->assets.s_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->SO_texts, &w->assets.s_wall.height, &w->assets.s_wall.width);
	w->assets.e_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->EA_texts, &w->assets.e_wall.height, &w->assets.e_wall.width);
	w->assets.w_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->WE_texts, &w->assets.w_wall.height, &w->assets.w_wall.width);
	w->assets.m_door.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/cdoor21.xpm", &w->assets.m_door.height,
			&w->assets.m_door.width);
	err = load_bonus_boom(w);
	err += load_bonus_cloud(w);
	if (w->assets.n_wall.img_ptr == NULL || w->assets.s_wall.img_ptr == NULL
		|| w->assets.e_wall.img_ptr == NULL || w->assets.w_wall.img_ptr == NULL
		|| w->assets.m_door.img_ptr == NULL || err != 0)
	{
		ft_printf("Error!\nCouldn't load sprites!\n");
		free_window(w);
		exit (EXIT_FAILURE);
	}
	load_all_address_sprites(w);
	return (0);
}

static bool	did_load_boom_fail(t_info *w)
{
	return (w->assets.b1.img_ptr == NULL || w->assets.b2.img_ptr == NULL
		|| w->assets.b3.img_ptr == NULL || w->assets.b4.img_ptr == NULL
		|| w->assets.b5.img_ptr == NULL || w->assets.b6.img_ptr == NULL
		|| w->assets.b7.img_ptr == NULL || w->assets.b8.img_ptr == NULL
		|| w->assets.b9.img_ptr == NULL || w->assets.b10.img_ptr == NULL);
}

static bool	did_load_cloud_fail(t_info *w)
{
	return (w->assets.c1.img_ptr == NULL || w->assets.c2.img_ptr == NULL
		|| w->assets.c3.img_ptr == NULL || w->assets.c4.img_ptr == NULL
		|| w->assets.c5.img_ptr == NULL || w->assets.c6.img_ptr == NULL
		|| w->assets.c7.img_ptr == NULL || w->assets.c8.img_ptr == NULL
		|| w->assets.c9.img_ptr == NULL || w->assets.c10.img_ptr == NULL);
}
