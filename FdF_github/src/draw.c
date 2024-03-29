/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:26:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/23 13:26:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void		ft_change_color(t_fdf *param)
{
	param->color += 1;
	if (param->color > 2)
		param->color = 0;
}

static int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double)len;
	increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double)len;
	increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double)len;
	new[0] = (R(startcolor)) + ft_round(pix * increment[0]);
	new[1] = (G(startcolor)) + ft_round(pix * increment[1]);
	new[2] = (B(startcolor)) + ft_round(pix * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

int	ft_get_color(t_fdf *fdf, int x, int y)
{
	int	mid_z;
	int	len;

	len = fdf->z_max - fdf->z_min;
	mid_z = ((float)fdf->z_max + (float)fdf->z_min) / 2;
	if (fdf->z_matrix[y][x].color != -1)
		return (fdf->z_matrix[y][x].color);
	else if (fdf->color == 0)
		if (fdf->z_matrix[y][x].z > mid_z)
			return (gradient(BROWN_LAND, GREEN_LAND, len,
					fdf->z_matrix[y][x].z));
		else
			return (gradient(BLUE_SEA, BROWN_LAND, len, fdf->z_matrix[y][x].z));
	else if (fdf->color == 1)
		if (fdf->z_matrix[y][x].z > mid_z)
			return (gradient(PINK, PURPLE, len, fdf->z_matrix[y][x].z));
		else
			return (gradient(WHITE, PINK, len, fdf->z_matrix[y][x].z));
	else if (fdf->color == 2)
	{
		if (fdf->z_matrix[y][x].z > mid_z)
			return (gradient(VIOLET, GOLD, len, fdf->z_matrix[y][x].z));
		else
			return (gradient(NAVY, VIOLET, len, fdf->z_matrix[y][x].z));
	}
	return (0);
}

void	ft_draw_line(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < (*fdf).height)
	{
		x = 0;
		while (x < (*fdf).width)
		{
			if (x < (*fdf).width - 1)
				ft_bressenham(x, y, (x + 1), y, fdf);
			if (y < (*fdf).height - 1)
				ft_bressenham(x, y, x, (y + 1), fdf);
			x++;
		}
		y++;
	}
	ft_menu(fdf);
}
