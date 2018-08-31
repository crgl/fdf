/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:56:24 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/30 10:56:31 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	confine_double(double x, double lbound, double rbound)
{
	if (x < lbound)
		return (lbound);
	if (x > rbound)
		return (rbound);
	return (x);
}

int		ct_words(char *s)
{
	int	ct;

	if (s == NULL)
		return (0);
	ct = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
			ct++;
		while (*s && *s != ' ')
			s++;
	}
	return (ct);
}

void	free_matrix(void ***twod)
{
	int	i;

	i = 0;
	if (*twod == NULL)
		return ;
	while ((*twod)[i] != NULL)
		free((*twod)[i++]);
	free(*twod);
	*twod = NULL;
}
