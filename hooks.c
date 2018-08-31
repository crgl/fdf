/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 13:00:57 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/30 13:01:03 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	back2basics(t_map *mapp)
{
	mapp->offset = D_0;
	mapp->center[0] = 0.5;
	mapp->center[1] = 0.5;
	ft_printf("%.0c", mapp->flags);
	mapp->theta = THETA_0;
	mapp->phi = PHI_0;
	mapp->stretch = STRETCH_0;
}

void	close_window(t_map *mapp)
{
	mlx_destroy_image(mapp->mlx_ptr, mapp->img.img_ptr);
	mlx_destroy_window(mapp->mlx_ptr, mapp->win_ptr);
	free_matrix((void ***)(&(mapp->coords)));
	exit(0);
}

int		clean_exit(void *param)
{
	close_window(param);
	return (0);
}

void	set_hooks(void *win_ptr, void *param)
{
	mlx_hook(win_ptr, 2, 0, &handle_key_press, param);
	mlx_hook(win_ptr, 3, 0, &handle_key_release, param);
	mlx_hook(win_ptr, 4, 0, &flip_on_click, param);
	mlx_hook(win_ptr, 5, 0, &flip_off_click, param);
	mlx_hook(win_ptr, 6, 0, &move_mouse, param);
	mlx_hook(win_ptr, 17, 0, &clean_exit, param);
}

int		refresh_window(void *param)
{
	t_map	*mapp;

	mapp = (t_map *)param;
	if (mapp->flags & HROTATE)
		mapp->theta = fmod(mapp->theta + HRSPEED, 2 * PI);
	if (mapp->flags & HROTATEB)
		mapp->theta = fmod(mapp->theta + 2 * PI - HRSPEED, 2 * PI);
	if (mapp->flags & VROTATE)
		if (mapp->phi + VRSPEED < PI / 2)
			mapp->phi += VRSPEED;
	if (mapp->flags & VROTATEB)
	{
		if (mapp->phi - VRSPEED > 0)
			mapp->phi -= VRSPEED;
	}
	place_coords(mapp);
	return (0);
}
