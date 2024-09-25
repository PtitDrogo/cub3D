#include "cub3D.h"

int	load_addr_sprites(t_image *image)
{
	image->pix_addr = mlx_get_data_addr(image->img_ptr, &image->bits_per_pixel,
			&image->size_line, &image->endian);
	if (!image->pix_addr)
		return (1);
	return (0);
}

void	load_sprites(t_info *w, t_parse_data *d)
{
	int	err;

	w->n_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->NO_texts, &w->n_wall.height, &w->n_wall.width);
	w->s_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->SO_texts, &w->s_wall.height, &w->s_wall.width);
	w->e_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->EA_texts, &w->e_wall.height, &w->e_wall.width);
	w->w_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->WE_texts, &w->w_wall.height, &w->w_wall.width);
	w->m_door.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			d->DO_texts, &w->w_wall.height, &w->w_wall.width);
	err = load_addr_sprites(&w->n_wall);
	err += load_addr_sprites(&w->s_wall);
	err += load_addr_sprites(&w->e_wall);
	err += load_addr_sprites(&w->w_wall);
	err += load_addr_sprites(&w->m_door);
	if (w->n_wall.img_ptr == NULL
		|| w->s_wall.img_ptr == NULL || w->e_wall.img_ptr == NULL
		|| w->w_wall.img_ptr == NULL || w->m_door.img_ptr == NULL
		|| err != 0)
	{
		ft_printf("Error!\nCouldn't load sprites!");
		free_window(w);
	}
	
}
