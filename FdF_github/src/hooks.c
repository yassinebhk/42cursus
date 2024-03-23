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

#include "fdf.h"

void	ft_my_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == 256 && keydata.action == MLX_PRESS)
		mlx_close_window(param);
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("Pressing L!");
	if (keydata.key == MLX_KEY_L && keydata.action == 0)
		puts(" Release L!");
}

void	ft_my_scrollhook(double xdelta, double ydelta, void *param)
{
	(void)param;
	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
}

void	ft_my_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		mlx_t *param1)
{
	int32_t	x;
	int32_t	y;

	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(param1, &x, &y);
		ft_printf("\nX: %d  Y: %d %d\n", x, y, param1->width);
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		puts("Right");
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
		puts("Middle");
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& mods == MLX_CONTROL)
		puts("Left + Control");
}
