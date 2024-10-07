/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:15:06 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 12:16:41 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_info		w;
	t_parse		data;

	init_game(&w, &data, argc, argv);
	mlx_hook(w.id_wind, MotionNotify, PointerMotionMask, mouse_movement, &w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, KeyRelease, KeyReleaseMask, release_countermeasure, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
	return (0);
}
