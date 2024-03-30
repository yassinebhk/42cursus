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

int		projection(int a);
int		ft_get_color(t_fdf *fdf, int x, int y);
void	ft_isometric(float *x, float *y, int z, t_fdf *fdf);
void	ft_scale(t_fdf *fdf);
void	ft_bressenham(t_pos p1, t_pos p2, t_fdf *fdf);

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

int	ft_get_color(t_fdf *fdf, int x, int y)
{
	int	mid_z;
	int	len;

	len = fdf->z_max - fdf->z_min;
	mid_z = ((float)fdf->z_max + (float)fdf->z_min) / 2;
	if (fdf->z_matrix[y][x].color != -1)
		return (fdf->z_matrix[y][x].color);
	else if (fdf->color == 0)
	{
		ft_choose_color(&fdf->z_matrix[y][x], 0);
		return (ft_z(fdf->z_matrix[y][x], fdf->z_matrix[y][x].z, mid_z, len));
	}
	else if (fdf->color == 1)
	{
		ft_choose_color(&fdf->z_matrix[y][x], 1);
		return (ft_z(fdf->z_matrix[y][x], fdf->z_matrix[y][x].z, mid_z, len));
	}
	else if (fdf->color == 2)
	{
		ft_choose_color(&fdf->z_matrix[y][x], 2);
		return (ft_z(fdf->z_matrix[y][x], fdf->z_matrix[y][x].z, mid_z, len));
	}
	return (0);
}

void	ft_bressenham(t_pos p1, t_pos p2, t_fdf *fdf)
{
	t_delta	delta;
	float	max;

	fdf->x = p1.x;
	fdf->y = p1.y;
	fdf->x1 = p2.x;
	fdf->y1 = p2.y;
	ft_scale(fdf);
	delta.x = fdf->x1 - fdf->x;
	delta.y = fdf->y1 - fdf->y;
	if (fabs(delta.x) > fabs(delta.y))
		max = fabs(delta.x);
	else
		max = fabs(delta.y);
	delta.x = delta.x / max;
	delta.y = delta.y / max;
	while (((int)(fdf->x - fdf->x1) || (int)(fdf->y - fdf->y1)))
	{
		if (fdf->x < 0 || fdf->x > WIDTH || fdf->y < 0 || fdf->y > HEIGHT)
			break ;
		mlx_pixel_put(fdf->mlx_ptr, fdf->win, fdf->x, fdf->y, ft_get_color(fdf,
				p2.x, p2.y));
		fdf->x += delta.x;
		fdf->y += delta.y;
	}
}
