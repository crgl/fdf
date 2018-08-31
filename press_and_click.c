/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_and_click.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 15:46:26 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/28 15:46:37 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_key_press(int key, void *param)
{
	t_map	*mapp;

	mapp = (t_map *)param;
	if (key == 53)
		close_window(param);
	else if (key == 49)
		back2basics(param);
	else if (key == 256)
		mapp->flags |= ZOOM;
	else if (key == 259)
		mapp->flags |= STRETCH;
	else if (key == 124)
		mapp->flags |= HROTATE;
	else if (key == 126)
		mapp->flags |= VROTATE;
	else if (key == 123)
		mapp->flags |= HROTATEB;
	else if (key == 125)
		mapp->flags |= VROTATEB;
	return (0);
}

int		handle_key_release(int key, void *param)
{
	t_map	*mapp;

	mapp = (t_map *)param;
	if (key == 256)
		mapp->flags &= ~ZOOM;
	else if (key == 259)
		mapp->flags &= ~STRETCH;
	else if (key == 124)
		mapp->flags &= ~HROTATE;
	else if (key == 126)
		mapp->flags &= ~VROTATE;
	else if (key == 123)
		mapp->flags &= ~HROTATEB;
	else if (key == 125)
		mapp->flags &= ~VROTATEB;
	return (0);
}

int		flip_on_click(int button, int x, int y, void *param)
{
	t_map	*mapp;

	(void)button;
	mapp = (t_map *)param;
	mapp->flags |= CLICKED;
	mapp->base.start[0] = x;
	mapp->base.start[1] = y;
	mapp->base.boffset = mapp->offset;
	mapp->base.bstretch = mapp->stretch;
	mapp->base.bcenter[0] = mapp->center[0];
	mapp->base.bcenter[1] = mapp->center[1];
	return (0);
}

int		flip_off_click(int button, int x, int y, void *param)
{
	t_map	*mapp;

	(void)x;
	(void)y;
	(void)button;
	mapp = (t_map *)param;
	mapp->flags &= ~CLICKED;
	return (0);
}

int		move_mouse(int x, int y, void *param)
{
	t_map	*mapp;

	mapp = (t_map *)param;
	if (!(mapp->flags & CLICKED))
		return (0);
	if (mapp->flags & ZOOM)
	{
		mapp->offset = mapp->base.boffset + 1.0 * (y - mapp->base.start[1]) /
						(double)mapp->img.height;
		if (mapp->offset < 1.0)
			mapp->offset = 1.0;
	}
	else if (mapp->flags & STRETCH)
		mapp->stretch = mapp->base.bstretch + 1.0 * (y - mapp->base.start[1]) /
							(double)mapp->img.height;
	else
	{
		mapp->center[0] = mapp->base.bcenter[0] +
			(1.0 * (x - mapp->base.start[0]) / (double)mapp->img.width);
		mapp->center[1] = mapp->base.bcenter[1] +
			(1.0 * (y - mapp->base.start[1]) / (double)mapp->img.height);
		mapp->center[0] = confine_double(mapp->center[0], 0, 1);
		mapp->center[1] = confine_double(mapp->center[1], 0, 1);
	}
	return (0);
}
