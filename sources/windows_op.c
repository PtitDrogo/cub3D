#include "cub3D.h"

static void	free_mlx_map(t_info *w);

int	load_window(t_info *w)
{
	w->id_mlx = mlx_init();
	if (w->id_mlx == NULL)
	{
		ft_printf(" Error \n/!\\ mlx init failed!\n");
		ft_free_array((void *)w->map_file);
		exit(0);
	}
	w->id_wind = mlx_new_window(w->id_mlx,
			DEFAULT_LENGTH, DEFAULT_HEIGHT , "My beautiful cube...");
	if (w->id_wind == NULL)
	{
		free_mlx_map(w);
		ft_printf(" Error \n/!\\ couldn't open window!\n");
		exit(0);
	}
	return (0);
}


int	free_window(t_info *w)
{
	if (w->m_door.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->m_door.img_ptr);
	if (w->n_wall.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->n_wall.img_ptr);
	if (w->s_wall.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->s_wall.img_ptr);
	if (w->e_wall.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->e_wall.img_ptr);
	if (w->w_wall.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->w_wall.img_ptr);
	if (w->boom1.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->boom1.img_ptr);
	if (w->boom2.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->boom2.img_ptr);
	if (w->boom3.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->boom3.img_ptr);
	if (w->boom4.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->boom4.img_ptr);
	if (w->boom5.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->boom5.img_ptr);
	if (w->img_buffer.img_ptr != NULL)
		mlx_destroy_image(w->id_mlx, w->img_buffer.img_ptr);
	mlx_destroy_window(w->id_mlx, w->id_wind);
	free_mlx_map(w);
	return (0);
}

static void	free_mlx_map(t_info *w)
{
	mlx_destroy_display(w->id_mlx);
	ft_free_array((void *)w->map_file);
	free(w->id_mlx);
	exit(0);
}
