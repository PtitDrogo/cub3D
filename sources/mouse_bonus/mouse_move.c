#include "cub3D.h"

static void	re_center_mouse(t_info *w, int x, int y);

int	mouse_movement(int x, int y, t_info *w)
{
	static int	prev_x = DEFAULT_LENGTH / 2;

	(void)y;
	if (x == prev_x)
		return (0);
	if (x < prev_x)
		rotate_camera(w, -1);
	else if (x > prev_x)
		rotate_camera(w, 1);
	re_center_mouse(w, x, y);
	prev_x = x;
	return (0);
}

static void	re_center_mouse(t_info *w, int x, int y)
{
	int	padding;
	int	x_center;
	int	y_center;

	padding = 40;
	x_center = DEFAULT_LENGTH / 2;
	y_center = DEFAULT_HEIGHT / 2;
	if (x + padding >= DEFAULT_LENGTH || x <= 0 + padding)
		mlx_mouse_move(w->id_mlx, w->id_wind, x_center, y_center);
	else if (y + padding >= DEFAULT_HEIGHT || y <= 0 + padding)
		mlx_mouse_move(w->id_mlx, w->id_wind, x_center, y_center);
}
