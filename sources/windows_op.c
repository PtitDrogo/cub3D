/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <lchapard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:53:50 by lchapard          #+#    #+#             */
/*   Updated: 2024/09/04 13:53:51 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	load_window(t_info *w)
{
	w->id_mlx = mlx_init();
	if (w->id_mlx == NULL)
	{
		ft_printf(" Error \n/!\\ mlx init failed!\n");
		exit(0); // free all
	}
	w->id_wind = mlx_new_window(w->id_mlx,
			w->w_lenght, w->w_height, "My beautiful cube...");
	if (w->id_wind == NULL)
	{
		mlx_destroy_display(w->id_mlx);
		free(w->id_mlx);
		ft_printf(" Error \n/!\\ couldn't open window!\n");
		exit(0); // free all
	}
	return (1);
}