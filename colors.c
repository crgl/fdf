/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:52:53 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/30 10:53:04 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_blend(unsigned int c1, unsigned int c2, double ratio)
{
	int	c3;

	c3 = (unsigned int)round(((c2 >> 8) & 0xff) * ratio +
			((c1 >> 8) & 0xff) * (1 - ratio)) << 8;
	c3 |= (unsigned int)round((c2 & 0xff) * ratio +
			(c1 & 0xff) * (1.0 - ratio));
	c3 |= (unsigned int)round(((c2 >> 16) & 0xff) * ratio +
			((c1 >> 16) & 0xff) * (1 - ratio)) << 16;
	return (c3);
}

void			ft_color_pixel(int x, int y, t_imgdata *img, unsigned int rgb)
{
	int				bytespp;
	int				i;
	unsigned int	color;

	color = mlx_get_color_value(img->mlx_ptr, rgb);
	bytespp = img->bpp / 8;
	i = 0;
	if (x >= img->width || y >= img->height || x <= 0 || y <= 0)
		return ;
	while (i < bytespp)
	{
		img->img_loc[x * bytespp + img->sl * y + ENDIND(img->ndn)] =
			(color >> (8 * i)) & 0xff;
		i++;
	}
}
