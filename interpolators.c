/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 20:19:14 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/20 20:19:20 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_straight(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color)
{
	int	ct;
	int	num_pixels;
	int	flip;

	ct = -1;
	if (p2[0] == p1[0])
	{
		flip = -2 * (p1[1] < p2[1]) + 1;
		num_pixels = flip * (p1[1] - p2[1]);
		while (++ct < num_pixels)
			ft_color_pixel(p1[0], p1[1] - flip * ct, &(mapp->img),
				color_blend(color[0], color[1], ct / (double)num_pixels));
	}
	else
	{
		flip = -2 * (p1[0] < p2[0]) + 1;
		num_pixels = flip * (p1[0] - p2[0]);
		while (++ct < num_pixels)
			ft_color_pixel(p1[0] - flip * ct, p1[1], &(mapp->img),
				color_blend(color[0], color[1], ct / (double)num_pixels));
	}
}

void	ip00(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color)
{
	int		ct;
	double	inc;

	ct = -1;
	if (p2[0] == p1[0] || p2[1] == p1[1])
	{
		print_straight(p1, p2, mapp, color);
		return ;
	}
	if (p2[0] - p1[0] < p2[1] - p1[1])
	{
		inc = 1. / (p2[1] - p1[1]);
		while (++ct < p2[1] - p1[1])
			ft_color_pixel((int)lrint(p1[0] + ct * inc * (p2[0] - p1[0])),
				(int)lrint(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
	else
	{
		inc = 1. / (p2[0] - p1[0]);
		while (++ct < p2[0] - p1[0])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
}

void	ip01(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color)
{
	int		ct;
	double	inc;

	ct = -1;
	if (p2[0] == p1[0] || p2[1] == p1[1])
	{
		print_straight(p1, p2, mapp, color);
		return ;
	}
	if (p2[0] - p1[0] < p1[1] - p2[1])
	{
		inc = 1. / (p1[1] - p2[1]);
		while (++ct < p1[1] - p2[1])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
	else
	{
		inc = 1. / (p2[0] - p1[0]);
		while (++ct < p2[0] - p1[0])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
}

void	ip10(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color)
{
	int		ct;
	double	inc;

	ct = -1;
	if (p2[0] == p1[0] || p2[1] == p1[1])
	{
		print_straight(p1, p2, mapp, color);
		return ;
	}
	if (p1[0] - p2[0] < p2[1] - p1[1])
	{
		inc = 1. / (p2[1] - p1[1]);
		while (++ct < p2[1] - p1[1])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
	else
	{
		inc = 1. / (p1[0] - p2[0]);
		while (++ct < p1[0] - p2[0])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
}

void	ip11(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color)
{
	int		ct;
	double	inc;

	ct = -1;
	if (p2[0] == p1[0] || p2[1] == p1[1])
	{
		print_straight(p1, p2, mapp, color);
		return ;
	}
	if (p1[0] - p2[0] < p1[1] - p2[1])
	{
		inc = 1. / (p1[1] - p2[1]);
		while (++ct < p1[1] - p2[1])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
	else
	{
		inc = 1. / (p1[0] - p2[0]);
		while (++ct < p1[0] - p2[0])
			ft_color_pixel(round(p1[0] + ct * inc * (p2[0] - p1[0])),
				round(p1[1] + ct * inc * (p2[1] - p1[1])), &(mapp->img),
				color_blend(color[0], color[1], ct * inc));
	}
}
