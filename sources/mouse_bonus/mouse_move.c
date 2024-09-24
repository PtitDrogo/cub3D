#include "cub3D.h"

static void re_center_mouse(t_info *w, int x, int y);

int mouse_movement(int x, int y, t_info *w)
{
    static int prev_x = DEFAULT_LENGTH / 2;
    (void)y;
    if (x == prev_x)
        return (0);
    if (x < prev_x)
		rotate_camera(w, XK_Left);
	else if (x > prev_x)
		rotate_camera(w, XK_Right);
    re_center_mouse(w, x, y);
    prev_x = x;
    return (0);
}
//gotta use move mouse
static void re_center_mouse(t_info *w, int x, int y)
{
    int padding = 50;
    
    if (x + padding >= DEFAULT_LENGTH || x <= 0 + padding)
    {
        mlx_mouse_move(w->id_mlx, w->id_wind, DEFAULT_LENGTH / 2, DEFAULT_HEIGHT / 2);
        // *x = DEFAULT_LENGTH / 2;
        // *y = DEFAULT_HEIGHT / 2;
    }
    if (y + padding >= DEFAULT_HEIGHT || y <= 0 + padding)
    {
        mlx_mouse_move(w->id_mlx, w->id_wind, DEFAULT_LENGTH / 2, DEFAULT_HEIGHT / 2);
        // *x = DEFAULT_LENGTH / 2;
        // *y = DEFAULT_HEIGHT / 2;
    }


}
