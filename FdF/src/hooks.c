/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:20:49 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/23 13:20:50 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/keycodes.h"
#include "../include/mousecodes.h"

int			ft_my_keyhook(int keydata, t_fdf *param);
int			mouse_press(int button, int x, int y, t_fdf *data);
static void	ft_move(t_fdf *param, int keydata);
static void	ft_rotation(t_fdf *param, int keydata);
static void	set_move_coords(int x, int y, t_fdf *data);

static void	ft_move(t_fdf *param, int keydata)
{
	if (keydata == 123)
		param->shift_x -= 20;
	else if (keydata == 124)
		param->shift_x += 20;
	else if (keydata == 126)
		param->shift_y -= 20;
	else if (keydata == 125)
		param->shift_y += 20;
}

static void	ft_rotation(t_fdf *param, int keydata)
{
	if (keydata == 69)
		param->zoom += 1;
	else if (keydata == 78 && param->zoom - 0.5 > 0)
		param->zoom -= 1;
	else if (keydata == 7)
	{
		param->anglex = ft_angle(param->anglex, 0.2);
		param->angley = ft_angle(param->anglex, 0.2);
	}
	else if (keydata == 16)
	{
		param->anglex = ft_angle(param->anglex, -0.2);
		param->angley = ft_angle(param->anglex, -0.2);
	}
	else if (keydata == 12)
	{
		param->anglex = ft_angle(param->anglex, -M_PI);
		param->angley = ft_angle(param->angley, -M_PI);
	}
	else if (keydata == 32)
		param->depth += 1;
	else if (keydata == 2)
		param->depth -= 1;
}

int	ft_my_keyhook(int keydata, t_fdf *param)
{
	mlx_clear_window(param->mlx_ptr, param->win);
	if (keydata == 53)
		ft_exit(param);
	else if (keydata == 123 || keydata == 124 || keydata == 125
		|| keydata == 126)
		ft_move(param, keydata);
	else if (keydata == 69 || keydata == 78 || keydata == 7 || keydata == 16
		|| keydata == 32 || keydata == 2 || keydata == 12)
		ft_rotation(param, keydata);
	else if (keydata == 35)
		param->p = projection(param->p);
	else if (keydata == 36)
		ft_reset(param);
	else if (keydata == 8)
		ft_change_color(param);
	ft_menu(param);
	ft_draw_line(param);
	return (0);
}

static void	set_move_coords(int x, int y, t_fdf *data)
{
	if (x < 0 || y < 0)
		return ;
	data->shift_x = x;
	data->shift_y = y;
}

int	mouse_press(int button, int x, int y, t_fdf *data)
{
	mlx_clear_window(data->mlx_ptr, data->win);
	if (button == LEFT_CLICK)
		set_move_coords(x, y, data);
	ft_draw_line(data);
	ft_menu(data);
	return (0);
}
