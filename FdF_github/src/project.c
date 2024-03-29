/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:28:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/25 14:28:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	projection(int a)
{
	if (a == 1)
		return (0);
	return (1);
}

void	ft_isometric(float *x, float *y, int z, t_fdf *fdf)
{
	*x = (*x - *y) * cos(fdf->anglex);
	*y = (*x + *y) * sin(fdf->angley) - z;
}

void	ft_scale(t_fdf *fdf)
{
	int	z2;
	int	z1;

	z1 = fdf->z_matrix[(int)fdf->y][(int)fdf->x].z * fdf->depth;
	z2 = fdf->z_matrix[(int)fdf->y1][(int)fdf->x1].z * fdf->depth;
	fdf->x *= fdf->zoom;
	fdf->y *= fdf->zoom;
	fdf->x1 *= fdf->zoom;
	fdf->y1 *= fdf->zoom;
	if (fdf->p == 1)
	{
		ft_isometric(&fdf->x, &fdf->y, z1, fdf);
		ft_isometric(&fdf->x1, &fdf->y1, z2, fdf);
	}
	fdf->x += fdf->shift_x;
	fdf->y += fdf->shift_y;
	fdf->x1 += fdf->shift_x;
	fdf->y1 += fdf->shift_y;
}

void	ft_bressenham(int x1, int y1, int x2, int y2, t_fdf *fdf)
{
	float	dx;
	float	dy;
	float	max;

	fdf->x = x1;
	fdf->y = y1;
	fdf->x1 = x2;
	fdf->y1 = y2;
	ft_scale(fdf);
	dx = fdf->x1 - fdf->x;
	dy = fdf->y1 - fdf->y;
	max = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx = dx / max;
	dy = dy / max;
	while (((int)(fdf->x - fdf->x1) || (int)(fdf->y - fdf->y1)))
	{
		if (fdf->x < 0 || fdf->x > WIDTH || fdf->y < 0 || fdf->y > HEIGHT)
			break ;
		mlx_pixel_put(fdf->mlx_ptr, fdf->win, fdf->x, fdf->y, ft_get_color(fdf,
				x2, y2));
		fdf->x += dx;
		fdf->y += dy;
	}
}
