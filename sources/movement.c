/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:26:12 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:56:02 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void			move_verticaly(t_info *w, int dir);
static void			move_horizontaly(t_info *w, int dir);
static double		get_wall_coef(double m_vector);

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
	double	save_dir_x;
	double	save_plane_x;
	double	cam;

	cam = coef * CAM_SPEED;
	save_dir_x = w->vectors.x_pos;
	w->vectors.x_pos = w->vectors.x_pos * cos(cam) - w->vectors.y_pos * sin(cam);
	w->vectors.y_pos = save_dir_x * sin(cam) + w->vectors.y_pos * cos(cam);
	save_plane_x = w->vectors.x_cam;
	w->vectors.x_cam = w->vectors.x_cam * cos(cam) - w->vectors.y_cam * sin(cam);
	w->vectors.y_cam = save_plane_x * sin(cam) + w->vectors.y_cam * cos(cam);
}

static void	move_verticaly(t_info *w, int dir)
{
	double	coef;
	double	step_x;
	double	step_y;
	char	c;

	step_x = w->vectors.x_pos * w->player_speed * dir;
	step_y = w->vectors.y_pos * w->player_speed * dir;
	coef = get_wall_coef(w->vectors.x_pos) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl + coef + step_x)];
	if (c != '1' && c != 'D')
	{
		w->x_pl += step_x;
	}
	coef = get_wall_coef(w->vectors.y_pos) * dir;
	c = w->actual_map[(int)(w->y_pl + coef + step_y)][(int)(w->x_pl)];
	if (c != '1' && c != 'D')
	{
		w->y_pl += step_y;
	}
}

static void	move_horizontaly(t_info *w, int dir)
{
	double	step_x;
	double	step_y;
	double	coef;
	char	c;

	step_x = w->vectors.x_cam * w->player_speed * dir;
	step_y = w->vectors.y_cam * w->player_speed * dir;
	coef = get_wall_coef(w->vectors.x_cam) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl + coef + step_x)];
	if (c != '1' && c != 'D')
	{
		w->x_pl += step_x;
	}
	coef = get_wall_coef(w->vectors.y_cam) * dir;
	c = w->actual_map[(int)(w->y_pl + coef + step_y)][(int)(w->x_pl)];
	if (c != '1' && c != 'D')
	{
		w->y_pl += step_y;
	}
	return ;
}

static double	get_wall_coef(double m_vector)
{
	double	coef;

	if (m_vector > 0)
		coef = MAX_ZOOM;
	else
		coef = -MAX_ZOOM;
	return (coef);
}
