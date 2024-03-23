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

#include "fdf.h"

line_t  ft_line_ec(double x1, double y1, double x2, double y2)
{   
    line_t line;

    printf("\nx1: %f y1: %f x2: %f y2: %f\n", x1, y1, x2, y2);
    line.m = (y2 - y1) / (x2 - x1);
    line.n = y1 - line.m * x1;
    return (line);
}

void    ft_draw_axis(mlx_image_t *img)
{
    int i;
    double ypos;
    line_t line;

    i = -1;
    ypos = ((WIDTH / 2) * sin(M_PI_6)) / (sin(M_PI_3)) + HEIGHT / 2;
    line = ft_line_ec(0, ypos, WIDTH / 2, HEIGHT / 2);
    while (++i < WIDTH / 2)
        mlx_put_pixel(img, i, line.m * i + line.n, 0x0000FFFF);
    line = ft_line_ec(WIDTH / 2, HEIGHT / 2, WIDTH, ypos);
    while (i < WIDTH)
    {
        mlx_put_pixel(img, i, line.m * i + line.n, 0x0000FFFF);
        i++;
    }
    ft_draw_x(img, 400, 0, HEIGHT/2);

}

void	ft_draw_table(mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			mlx_put_pixel(img, WIDTH - 1, j, 0xFFFFFFFF);
			mlx_put_pixel(img, i, j, 0xFFFFFFFF);
			j++;
		}
		i = i + 80;
	}
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			mlx_put_pixel(img, i, HEIGHT - 1, 0xFFFFFFFF);
			mlx_put_pixel(img, i, j, 0xFFFFFFFF);
			i++;
		}
		j = j + 60;
	}
}

void	ft_draw_x(mlx_image_t *img, int i, int j, int jmax)
{
	while (j < jmax)
	{
        if (i == 400  && jmax == HEIGHT/2)
            mlx_put_pixel(img, i, j, 0x0000FFFF);
        else
		    mlx_put_pixel(img, i, j, 0xFF000040);
		j++;
	}
}

void	ft_draw_y(mlx_image_t *img, int i, int imax, int j)
{
	while (i < imax)
	{
		mlx_put_pixel(img, i, j, 0xFF000004);
		i++;
	}
}

void	ft_draw_number(mlx_image_t *img)
{
	int	i;
	int	j;

	i = 81;
	while (i < 160)
	{
		ft_draw_x(img, i, 61, 300);
		ft_draw_x(img, i + 160, 61, HEIGHT - 60);
		i++;
	}
	j = 241;
	while (j < 300)
	{
		ft_draw_y(img, 160, 241, j);
		j++;
	}
	ft_draw_y(img, 401, 720, 61);
	ft_draw_y(img, 401, 720, 539);
	ft_draw_y(img, 401, 640, 179);
	ft_draw_y(img, 401, 640, 299);
	ft_draw_y(img, 481, 720, 421);
	ft_draw_y(img, 481, 720, 361);
	ft_draw_x(img, 401, 61, 180);
	ft_draw_x(img, 719, 61, 360);
	ft_draw_x(img, 719, 421, 540);
	ft_draw_x(img, 481, 361, 420);
	ft_draw_x(img, 401, 301, 540);
	ft_draw_x(img, 401, 421, 540);
	ft_draw_x(img, 639, 181, 300);
}
