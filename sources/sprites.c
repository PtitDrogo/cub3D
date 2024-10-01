#include "cub3D.h"

int	load_addr_sprites(t_image *image)
{
	image->pix_addr = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel,
			&image->size_line, &image->endian);
	if (!image->pix_addr)
		return (1);
	return (0);
}

int	load_bonus_sprites(t_info *w)
{
	//Added for animation (proper w and h attribution)
	w->boom1.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom1.xpm",  &w->boom1.width, &w->boom1.height);
	w->boom2.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom2.xpm", &w->boom2.width, &w->boom2.height);
	w->boom3.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom3.xpm", &w->boom3.width, &w->boom3.height);
	w->boom4.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom4.xpm", &w->boom4.width, &w->boom4.height);
	w->boom5.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom5.xpm", &w->boom5.width, &w->boom5.height);
	if (w->boom1.img_ptr == NULL || w->boom2.img_ptr == NULL 
		|| w->boom3.img_ptr == NULL || w->boom4.img_ptr == NULL
		|| w->boom5.img_ptr == NULL)
	{
		return (1);
	}
	return (0);
}

int	set_addr_sprites_bonus(t_info *w)
{
	int	err;

	err = load_addr_sprites(&w->boom1);
	err += load_addr_sprites(&w->boom2);
	err += load_addr_sprites(&w->boom3);
	err += load_addr_sprites(&w->boom4);
	err += load_addr_sprites(&w->boom5);
	if (err)
		return (1);
	return (0);
}

int	set_addr_sprites(t_info *w)
{
	int	err;

	err = load_addr_sprites(&w->n_wall);
	err += load_addr_sprites(&w->s_wall);
	err += load_addr_sprites(&w->e_wall);
	err += load_addr_sprites(&w->w_wall);
	err += load_addr_sprites(&w->m_door);
	if (err)
		return (1);
	return (0);
}

int	load_sprites(t_info *w, t_parse_data *d, int err)
{
	w->n_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		d->NO_texts, &w->n_wall.height, &w->n_wall.width);
	w->s_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		d->SO_texts, &w->s_wall.height, &w->s_wall.width);
	w->e_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		d->EA_texts, &w->e_wall.height, &w->e_wall.width);
	w->w_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		d->WE_texts, &w->w_wall.height, &w->w_wall.width);
	w->m_door.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		d->DO_texts, &w->m_door.height, &w->m_door.width);
	err = load_bonus_sprites(w);
	if (w->n_wall.img_ptr == NULL || w->s_wall.img_ptr == NULL
		|| w->e_wall.img_ptr == NULL || w->w_wall.img_ptr == NULL
		|| w->m_door.img_ptr == NULL || err != 0)
	{
		ft_printf("Error!\nCouldn't load sprites!\n");
		free_window(w);
		return (1);
	}
	err = set_addr_sprites(w);
	err += set_addr_sprites_bonus(w);
	if (err)
	{
		ft_printf("Error!\nCouldn't set sprite adress!\n");
		free_window(w);
		return (1);
	}
	return (0);
}
