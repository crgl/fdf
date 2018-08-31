/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_squad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 13:27:56 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/30 13:28:03 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project(t_fpt3d sp, t_pt2d dp, t_map *mapp)
{
	double	tmp;
	double	k;
	double	x;
	double	y;

	x = (sp[0] - mapp->center[0]);
	y = (mapp->center[1] - sp[1]);
	k = (CAM2SCREEN + fabs((x * sin(mapp->theta) + y * cos(mapp->theta)) *
			cos(mapp->phi) + mapp->offset)) / CAM2SCREEN;
	tmp = (x * cos(mapp->theta) - y * sin(mapp->theta)) / k;
	dp[0] = (int)round(mapp->img.width / 2.0 +
				tmp * (mapp->img.width * 4 / 5.0));
	tmp = ((x * sin(mapp->theta) + y * cos(mapp->theta)) * sin(mapp->phi) +
			sp[2] * mapp->stretch * cos(mapp->phi)) / k;
	dp[1] = (int)round(mapp->img.height / 2.0 -
				tmp * (mapp->img.height * 4 / 5.0));
}

void	place_line(t_fpt3d fp1, t_fpt3d fp2, t_map *mapp)
{
	t_pt2d				p1;
	t_pt2d				p2;
	static const t_ip	fns[2][2] = { {&ip00, &ip01}, {&ip10, &ip11} };

	project(fp1, p1, mapp);
	project(fp2, p2, mapp);
	if ((p1[0] < 0 || p1[0] > mapp->img.width ||
		p1[1] < 0 || p1[1] > mapp->img.height) &&
		(p2[0] < 0 || p2[0] > mapp->img.width ||
		p2[1] < 0 || p2[1] > mapp->img.height))
		return ;
	fns[p1[0] > p2[0]][p1[1] > p2[1]](p1, p2, mapp,
		(t_upt2d){color_blend(C1, C2, fp1[2]),
		color_blend(C1, C2, fp2[2])});
}

void	add_to_image(t_pt3d p1, t_pt3d p2, t_map *mapp)
{
	t_fpt3d	fp1;
	t_fpt3d	fp2;

	fp1[0] = p1[0] / (double)mapp->width;
	fp1[1] = p1[1] / (double)mapp->height;
	fp1[2] = (mapp->max == mapp->min) ? 0 : p1[2] /
				(double)(mapp->max - mapp->min);
	fp2[0] = p2[0] / (double)mapp->width;
	fp2[1] = p2[1] / (double)mapp->height;
	fp2[2] = (mapp->max == mapp->min) ? 0 : p2[2] /
				(double)(mapp->max - mapp->min);
	place_line(fp1, fp2, mapp);
}

void	place_coords(t_map *mapp)
{
	int			y;
	int			x;
	t_imgdata	*img;

	if (mapp->img.img_ptr != NULL)
		mlx_destroy_image(mapp->mlx_ptr, mapp->img.img_ptr);
	img = &(mapp->img);
	img->img_ptr = mlx_new_image(mapp->mlx_ptr, img->width, img->height);
	img->img_loc = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->sl,
					&img->ndn);
	y = -1;
	while (++y < mapp->height)
	{
		x = -1;
		while (++x < mapp->width)
		{
			if (y + 1 < mapp->height)
				add_to_image((t_pt3d){x, y, mapp->coords[y][x]},
					(t_pt3d){x, y + 1, mapp->coords[y + 1][x]}, mapp);
			if (x + 1 < mapp->width)
				add_to_image((t_pt3d){x, y, mapp->coords[y][x]},
					(t_pt3d){x + 1, y, mapp->coords[y][x + 1]}, mapp);
		}
	}
	mlx_put_image_to_window(mapp->mlx_ptr, mapp->win_ptr, img->img_ptr, 0, 0);
}
