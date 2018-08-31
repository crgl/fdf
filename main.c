/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 19:44:42 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/05 20:06:35 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		matrix_append(t_map *mapp, char *line)
{
	char	**snums;
	int		*row;
	int		len;
	int		**tmp;

	snums = ft_strsplit(line, ' ');
	len = mapp->width;
	if ((row = (int *)malloc((len) * sizeof(int))) == NULL)
		return (-1);
	while (len--)
	{
		row[len] = ft_atoi(snums[len]);
		mapp->min = (row[len] < mapp->min) ? row[len] : mapp->min;
		mapp->max = (row[len] > mapp->max) ? row[len] : mapp->max;
	}
	len = mapp->height;
	if ((tmp = ft_memalloc(sizeof(int *) * (len + 2))) == NULL)
		return (-1);
	tmp[len] = row;
	while (len--)
		tmp[len] = mapp->coords[len];
	free(mapp->coords);
	mapp->coords = tmp;
	free_matrix((void ***)&snums);
	return (1);
}

void	ft_makemap(char *input_file, t_map *mapp)
{
	int		fd;
	int		line_length;
	char	*line;

	mapp->coords = (int **)ft_memalloc(sizeof(int *));
	if ((fd = open(input_file, O_RDONLY)) == -1)
		return ;
	line_length = 0;
	mapp->height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line_length == 0)
			line_length = ct_words(line);
		mapp->width = line_length;
		if (ct_words(line) != line_length || matrix_append(mapp, line) == -1)
		{
			free(line);
			free_matrix((void ***)(&mapp->coords));
			return ;
		}
		free(line);
		mapp->height++;
	}
}

int		main(int argc, char **argv)
{
	t_map	mapp;

	if (argc != 2)
	{
		ft_putendl_fd("usage: ./fdf map.fdf", 2);
		return (argc);
	}
	ft_memset(&mapp, 0, sizeof(t_map));
	mapp.img.width = 1000;
	mapp.img.height = 1000;
	ft_makemap(argv[1], &mapp);
	if (!mapp.coords)
	{
		ft_putendl_fd("Invalid map", 2);
		return (argc);
	}
	mapp.mlx_ptr = mlx_init();
	mapp.win_ptr = mlx_new_window(mapp.mlx_ptr, mapp.img.width,
					mapp.img.height, "Death");
	back2basics(&mapp);
	place_coords(&mapp);
	set_hooks(mapp.win_ptr, &mapp);
	mlx_loop_hook(mapp.mlx_ptr, &refresh_window, &mapp);
	mlx_loop(mapp.mlx_ptr);
	return (0);
}
