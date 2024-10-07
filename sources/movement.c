/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:26:12 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:32:34 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		move_verticaly(t_info *w, int dir);
static void		move_horizontaly(t_info *w, int dir);
static double		get_WallCoef(double m_vector);

void	move_player(t_info *w)
{
	if (w->p_inputs.going_up == true)
		move_verticaly(w, 1);
	if (w->p_inputs.going_down == true)
		move_verticaly(w, -1);
	if (w->p_inputs.going_left == true)
		move_horizontaly(w, -1);
	if (w->p_inputs.going_right == true)
		move_horizontaly(w, 1);
	if (w->p_inputs.rotate_cam != 0)
		rotate_camera(w, w->p_inputs.rotate_cam);
}

void	rotate_camera(t_info *w, int coef)
{
	double	saveDirX;
	double	savePlaneX;
	double	camMultiplier;

	camMultiplier = coef * CAM_SPEED;
	saveDirX = w->vectors.xPos;
	w->vectors.xPos = w->vectors.xPos * cos(camMultiplier) - w->vectors.yPos * sin(camMultiplier);
	w->vectors.yPos = saveDirX * sin(camMultiplier) + w->vectors.yPos * cos(camMultiplier);
	savePlaneX = w->vectors.xCam;
	w->vectors.xCam = w->vectors.xCam * cos(camMultiplier) - w->vectors.yCam * sin(camMultiplier);
	w->vectors.yCam = savePlaneX * sin(camMultiplier) + w->vectors.yCam * cos(camMultiplier);
}

static void	move_verticaly(t_info *w, int dir)
{
	double	coef;
	double	stepX;
	double	stepY;
	char	c;
	
	stepX = w->vectors.xPos * w->player_speed * dir;
	stepY = w->vectors.yPos * w->player_speed * dir;
	coef = get_WallCoef(w->vectors.xPos) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl +coef + stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl += stepX;
	}
	coef = get_WallCoef(w->vectors.yPos) * dir;
	c = w->actual_map[(int)(w->y_pl +coef + stepY)][(int)(w->x_pl)];
	if(c != '1' && c != 'D')
	{
		w->y_pl += stepY;
	}
}

static void    move_horizontaly(t_info *w, int dir)
{
	double	stepX;
	double	stepY;
	double	coef;
	char	c;

	stepX = w->vectors.xCam * w->player_speed * dir;
	stepY = w->vectors.yCam * w->player_speed * dir;
	coef = get_WallCoef(w->vectors.xCam) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl +coef +stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl += stepX;
	}
	coef = get_WallCoef(w->vectors.yCam) * dir;
	c = w->actual_map[(int)(w->y_pl +coef + stepY)][(int)(w->x_pl)];
	if( c != '1' && c != 'D')
	{
		w->y_pl += stepY;
	}
}


static double	get_WallCoef(double m_vector)
{
	double	coef;
	if (m_vector > 0)
		coef = MAX_ZOOM;
	else
		coef = -MAX_ZOOM;
	return(coef);
}
