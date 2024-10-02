#include "cub3D.h"

static void load_all_address_sprites(t_info *w);

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
	w->assets.boom1.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom1.xpm",  &w->assets.boom1.width, &w->assets.boom1.height);
	w->assets.boom2.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom2.xpm", &w->assets.boom2.width, &w->assets.boom2.height);
	w->assets.boom3.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom3.xpm", &w->assets.boom3.width, &w->assets.boom3.height);
	w->assets.boom4.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom4.xpm", &w->assets.boom4.width, &w->assets.boom4.height);
	w->assets.boom5.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom5.xpm", &w->assets.boom5.width, &w->assets.boom5.height);
	w->assets.boom6.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom6.xpm", &w->assets.boom6.width, &w->assets.boom6.height);
	w->assets.boom7.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom7.xpm", &w->assets.boom7.width, &w->assets.boom7.height);
	w->assets.boom8.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom8.xpm", &w->assets.boom8.width, &w->assets.boom8.height);
	w->assets.boom9.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom9.xpm", &w->assets.boom9.width, &w->assets.boom9.height);
	w->assets.boom10.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/boom10.xpm", &w->assets.boom10.width, &w->assets.boom10.height);
	if (w->assets.boom1.img_ptr == NULL || w->assets.boom2.img_ptr == NULL 
		|| w->assets.boom3.img_ptr == NULL || w->assets.boom4.img_ptr == NULL
		|| w->assets.boom5.img_ptr == NULL || w->assets.boom6.img_ptr == NULL
		|| w->assets.boom7.img_ptr == NULL || w->assets.boom8.img_ptr == NULL
		|| w->assets.boom9.img_ptr == NULL || w->assets.boom10.img_ptr == NULL)
	{
		return (1);
	}
	return (0);
}

int	load_bonus_sprites2(t_info *w)
{
	//Added for animation (proper w and h attribution)
	w->assets.cloud1.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud1.xpm",  &w->assets.cloud1.width, &w->assets.cloud1.height);
	w->assets.cloud2.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud2.xpm", &w->assets.cloud2.width, &w->assets.cloud2.height);
	w->assets.cloud3.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud3.xpm", &w->assets.cloud3.width, &w->assets.cloud3.height);
	w->assets.cloud4.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud4.xpm", &w->assets.cloud4.width, &w->assets.cloud4.height);
	w->assets.cloud5.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud5.xpm", &w->assets.cloud5.width, &w->assets.cloud5.height);
	w->assets.cloud6.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud6.xpm",  &w->assets.cloud6.width, &w->assets.cloud6.height);
	w->assets.cloud7.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud7.xpm", &w->assets.cloud7.width, &w->assets.cloud7.height);
	w->assets.cloud8.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud8.xpm", &w->assets.cloud8.width, &w->assets.cloud8.height);
	w->assets.cloud9.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud9.xpm", &w->assets.cloud9.width, &w->assets.cloud9.height);
	w->assets.cloud10.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
		"./sprites/cloud10.xpm", &w->assets.cloud10.width, &w->assets.cloud10.height);
	if (w->assets.cloud1.img_ptr == NULL || w->assets.cloud2.img_ptr == NULL 
		|| w->assets.cloud3.img_ptr == NULL || w->assets.cloud4.img_ptr == NULL
		|| w->assets.cloud5.img_ptr == NULL || w->assets.cloud6.img_ptr == NULL
		|| w->assets.cloud7.img_ptr == NULL || w->assets.cloud8.img_ptr == NULL
		|| w->assets.cloud9.img_ptr == NULL || w->assets.cloud10.img_ptr == NULL)
	{
		return (1);
	}
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
		"./sprites/cdoor21.xpm", &w->assets.m_door.height, &w->assets.m_door.width);
	err = load_bonus_sprites(w);
	err += load_bonus_sprites2(w);
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

//cadeau
static void load_all_address_sprites(t_info *w)
{
	int i;
	int end;
	int err;
	t_image *ptr;

	err = 0;
	ptr = (t_image *)&w->assets;
	end = sizeof(t_assets) / sizeof(t_image); //very big brain
	i = 0;
	while (i < end)
	{
		err += load_addr_sprites(&ptr[i]);
		i++;
	}
	if (err)
	{
		ft_printf("Error!\nCouldn't set sprite adress!\n");
		free_window(w);
		exit (EXIT_FAILURE);
	}
	return ;
}
