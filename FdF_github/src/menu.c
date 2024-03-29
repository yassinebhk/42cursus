/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:28:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/25 14:28:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	draw_title(t_fdf *data, int x, int *y)
{
	mlx_string_put(data->mlx_ptr, data->win, x, *y, WHITE,
		"/**********************\\");
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x, *y, WHITE,
		"*    Fil de Fer (FDF)  *");
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x, *y, WHITE,
		"\\**********************/");
	*y += 50;
}

static void	ft_print_nbr(t_fdf *fdf, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(fdf->mlx_ptr, fdf->win, x, y, WHITE, str);
	free(str);
}

static void	draw_map_info1(t_fdf *data, int x, int *y)
{
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "WIDTH");
	*y += 25;
	ft_print_nbr(data, x + 50, *y, data->width);
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "HEIGHT");
	*y += 25;
	ft_print_nbr(data, x + 50, *y, data->height);
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "DEPTH");
	*y += 25;
	ft_print_nbr(data, x + 50, *y, data->depth);
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "ZOOM");
	*y += 25;
	ft_print_nbr(data, x + 50, *y, data->zoom);
	*y += 25;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "PROYECTION");
	*y += 25;
	if (data->p == 1)
		mlx_string_put(data->mlx_ptr, data->win, x + 50, *y, WHITE, "ISO");
	else
		mlx_string_put(data->mlx_ptr, data->win, x + 50, *y, WHITE, "PARALLEL");
}

static void	draw_controls(t_fdf *data, int x, int *y)
{
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y, WHITE, "ZOOM");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 25, WHITE, "-> + \
		-");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 50, WHITE, "MOVE");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 75, WHITE,
		"-> arrows");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 100, WHITE,
		"-> click");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 125, WHITE, "ROTATE");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 150, WHITE, "-> x \
		/y");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 175, WHITE,
		"ROTATE 90º");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 200, WHITE, "-> q");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 225, WHITE, "RESET");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 250, WHITE,
		"-> enter");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 275, WHITE, "EXIT");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 300, WHITE, "-> esc");
	mlx_string_put(data->mlx_ptr, data->win, x + 25, *y + 325, WHITE,
		"Elevation/Depth");
	mlx_string_put(data->mlx_ptr, data->win, x + 50, *y + 350, WHITE, "-> u\
		/d");
	*y += 350;
}

void	ft_menu(t_fdf *data)
{
	int	width;
	int	height;
	int	x;
	int	y;

	x = 30;
	y = 30;
	draw_title(data, x, &y);
	mlx_string_put(data->mlx_ptr, data->win, x, y, WHITE, "/* MAP_INFO */");
	y += 30;
	draw_map_info1(data, x, &y);
	y += 60;
	mlx_string_put(data->mlx_ptr, data->win, x, y, WHITE,
		"/* CHANGE_PROYECTION */");
	y += 30;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, y, WHITE, "-> P");
	y += 60;
	mlx_string_put(data->mlx_ptr, data->win, x, y, WHITE, "/* COLOR_THEMES */");
	y += 30;
	mlx_string_put(data->mlx_ptr, data->win, x + 25, y, WHITE, "-> C");
	y += 60;
	mlx_string_put(data->mlx_ptr, data->win, x, y, WHITE, "/* MAP_CONTROLS */");
	y += 30;
	draw_controls(data, x, &y);
}
