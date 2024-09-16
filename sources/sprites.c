#include "cub3D.h"

void	load_sprites(t_info *w)
{
	w->m_door.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/chocbarre.xpm", &w->m_door.height, &w->m_door.width);
	w->n_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/chocbarre.xpm", &w->n_wall.height, &w->n_wall.width);
	w->s_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/chocbarre.xpm", &w->s_wall.height, &w->s_wall.width);
	w->e_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/chocbarre.xpm", &w->e_wall.height, &w->e_wall.width);
	w->w_wall.img_ptr = mlx_xpm_file_to_image(w->id_mlx,
			"./sprites/chocbarre.xpm", &w->w_wall.height, &w->w_wall.width);
	if (w->m_door.img_ptr == NULL || w->n_wall.img_ptr == NULL
		|| w->s_wall.img_ptr == NULL || w->e_wall.img_ptr == NULL
		|| w->w_wall.img_ptr == NULL)
	{
		ft_printf("Error!\nCouldn't load sprites!");
		free_window(w);
	}
}
