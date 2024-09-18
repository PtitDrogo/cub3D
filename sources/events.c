#include "cub3D.h"

static void		dda_innit(t_info *w, int i);
static void		apply_texture(t_info *w);
static t_image	*get_texture(t_info *w);
static void		draw_line(t_info *w, int x);
static int		pixel_color(t_info *data, int texture_y);

/*
	x = 0;
	while (x < SCREENWIDTH)
	{
		pre_dda(data->cast, player, x);
		dda(data->cast, data);
		apply_texture(data);
		draw_line(data->cast, data, x);
		x++;
	}
*/
int	no_events(t_info *w)
{
	int	i;

	i = 0;
	draw_floor_sky(DEFAULT_LENGTH, DEFAULT_HEIGHT, w);
	while (i < DEFAULT_LENGTH)
	{
		dda_innit(w, i);
		movetoFirstXY(w, w->rayDirX, w->rayDirY);
		w->distWall = applyDDA(w, 0);
		apply_texture(w);
		getDrawLimits(w);
		draw_line(w, i);
		//Add function here to draw the actual line
		i++;
	}
	mlx_put_image_to_window(w->id_mlx, w->id_wind, w->img_buffer.img_ptr, 0, 0);
	return (0);
}

static void	draw_line(t_info *w, int x)
{
	int	y;
	int	scaling;
	int	color;
	int	texture_y;

	y = w->draw_start;
	//We are going through every pixel of the vertical line and putting it in our buffer img;
	while (y <= w->draw_end)
	{
		scaling = (y * 256) - DEFAULT_HEIGHT * 128 + w->line_height * 128;
		texture_y = ((scaling * w->n_wall.height) / w->line_height) / 256;
		if (texture_y < 0)
			texture_y = 0; //Pour les segfaults dans les coins
		if (texture_y >= w->n_wall.height) //IMAGE TROP GROSSE LOL OU TROP PETITE QUI SAIT
			texture_y = w->n_wall.height - 1;
		color = pixel_color(w, texture_y);
		pixel_fill(&w->img_buffer, x, y, color);
		y++;
	}
}

static int	pixel_color(t_info *w, int texture_y)
{
	char	*color;
	t_image			*texture;

	texture = w->in_use_texture;

	color = texture->pix_addr + (texture_y * texture->size_line + w->texture_x * (texture->bits_per_pixel / 8));
	return (*color); //why are we casting this to unsigned int ? Very good question;
}

static void	apply_texture(t_info *w)
{
	double	touched_wall;

	w->in_use_texture = get_texture(w);
	if (w->side == 0)
		touched_wall = (w->distWall * w->rayDirY) + w->y_pl;
	else
		touched_wall = (w->distWall * w->rayDirX) + w->x_pl;
	touched_wall -= floor(touched_wall);
	w->texture_x = (int)(touched_wall * (double)w->n_wall.width); //It could be any texture i just want the standard width
	if ((w->side == 0 && w->vectors.xPos > 0) || (w->side == 1 && w->vectors.yPos < 0))
		w->texture_x = w->n_wall.width - w->texture_x - 1;
	/*
	The last condition checks if:
	The ray hit a vertical wall AND the player is facing right (positive X)
	OR
	The ray hit a horizontal wall AND the player is facing up (negative Y)
	If either of these conditions is true, the code flips the texture horizontally:
	data->texture_x = data->textures[0].width - data->texture_x - 1;
	This operation mirrors the texture coordinate. If texture_x was 10 in a 64-pixel wide texture, it becomes 53 (64 - 10 - 1).*/
}

static t_image	*get_texture(t_info *w)
{
	if (w->side == 0)
	{
		if (w->rayDirX > 0)
			return (&w->e_wall);
		else
			return (&w->s_wall);
	}
	else
	{
		if (w->rayDirY > 0)
			return (&w->w_wall);
		else
			return (&w->n_wall);
	}
}


static	void dda_innit(t_info *w, int i)
{
	w->cameraX = 2 * i / (double)DEFAULT_LENGTH - 1;
	w->rayDirX = w->vectors.xPos + w->vectors.xCam * w->cameraX;
	w->rayDirY = w->vectors.yPos + w->vectors.yCam * w->cameraX;
	w->current_map_x = (int)w->x_pl;
	w->current_map_y = (int)w->y_pl;
	if (w->rayDirX == 0)
		w->vectors.deltaX = 1e30;
	else
		w->vectors.deltaX = sqrt(1 + (w->rayDirY * w->rayDirY) / (w->rayDirX * w->rayDirX));
	if (w->rayDirY == 0)
		w->vectors.deltaY = 1e30;
	else
		w->vectors.deltaY = sqrt(1 + (w->rayDirX * w->rayDirX) / (w->rayDirY * w->rayDirY));
	return ;
}




void	rotate_camera(t_info *w, int id)
{
	double	rotSpeed;// to change
	double	saveDirX;
	double	savePlaneX;

	rotSpeed = 3.3; 
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


