#include "cub3D.h"

int	no_events(t_info *w)
{
	(void)w;
	return (0);
}

void	rotate_camera(t_info *w, int id)
{
	double	rotSpeed;// to change
	double	saveDirX;
	double	savePlaneX;

	rotSpeed = 0.3; 
	if (id == XK_Right)
	{
		saveDirX = w->vectors.xPos;
		w->vectors.xPos = w->vectors.xPos * cos(-rotSpeed) - w->vectors.yPos * sin(-rotSpeed);
		w->vectors.yPos = saveDirX * sin(-rotSpeed) + w->vectors.yPos * cos(-rotSpeed);
		savePlaneX = w->vectors.xCam;
		w->vectors.xCam = w->vectors.xCam * cos(-rotSpeed) - w->vectors.yCam * sin(-rotSpeed);
		w->vectors.yCam = savePlaneX * sin(-rotSpeed) + w->vectors.yCam * cos(-rotSpeed);
	}
	else
	{
		saveDirX = w->vectors.xPos;
		w->vectors.xPos = w->vectors.xPos * cos(rotSpeed) - w->vectors.yPos * sin(rotSpeed);
		w->vectors.yPos = saveDirX * sin(rotSpeed) + w->vectors.yPos * cos(rotSpeed);
		savePlaneX = w->vectors.xCam;
		w->vectors.xCam = w->vectors.xCam * cos(rotSpeed) - w->vectors.yCam * sin(rotSpeed);
		w->vectors.yCam = savePlaneX * sin(rotSpeed) + w->vectors.yCam * cos(rotSpeed);
	}
}

void	moove_u_d(t_info *w, int id)
{
	if (id == XK_w)
	{
		if(w->actual_map[(int)w->x_pl + (int)w->vectors.xPos * 2][(int)w->y_pl] == false)
			w->x_pl += w->vectors.xPos * 2;
		if(w->actual_map[(int)w->x_pl][(int)w->y_pl + (int)w->vectors.yPos * 2] == false)
			w->y_pl += w->vectors.yPos * 2;
	}
	else
	{
		if(w->actual_map[(int)w->x_pl - (int)w->vectors.xPos * 2][(int)w->y_pl] == false)
			w->x_pl -= w->vectors.xPos * 2;
		if(w->actual_map[(int)w->x_pl][(int)w->y_pl - (int)w->vectors.yPos * 2] == false)
			w->y_pl -= w->vectors.yPos * 2;
	}
}

void	moove_l_r(t_info *w, int id)
{
	if (id == XK_d)
	{
		if(w->actual_map[(int)w->x_pl + (int)w->vectors.xCam * 2][(int)w->y_pl] == false)
			w->x_pl += w->vectors.xCam * 2;
		if(w->actual_map[(int)w->x_pl][(int)w->y_pl + (int)w->vectors.yCam * 2] == false)
			w->y_pl += w->vectors.yCam * 2;
	}
	else
	{
		if(w->actual_map[(int)w->x_pl - (int)w->vectors.xCam * 2][(int)w->y_pl] == false)
			w->x_pl -= w->vectors.xCam * 2;
		if(w->actual_map[(int)w->x_pl][(int)w->y_pl - (int)w->vectors.yCam * 2] == false)
			w->y_pl -= w->vectors.yCam * 2;
	}
}

int	deal_key(int id_key, t_info *w)
{
	if (id_key == XK_Escape)
		free_window(w);
	if (id_key == XK_s || id_key == XK_w)
		moove_u_d(w, id_key); // avant arriere
	if (id_key == XK_d || id_key == XK_a)
		moove_l_r(w, id_key); // droite gauche
	if (id_key == XK_Left || id_key == XK_Right)
		rotate_camera(w, id_key); // droite gauche
	return (0);
}


