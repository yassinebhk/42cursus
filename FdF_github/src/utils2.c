/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 11:46:48 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_is_hex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a'
			&& c <= 'f') || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	ft_putnbr_dec(char *hex)
{
	int	length;
	int	base;
	int	decimal;

	length = ft_strlen(hex) - 1;
	base = 1;
	decimal = 0;
	while (length >= 0)
	{
		if (hex[length] >= '0' && hex[length] <= '9')
			decimal += (hex[length] - 48) * base;
		if (hex[length] >= 'A' && hex[length] <= 'F')
			decimal += (hex[length] - 55) * base;
		if (hex[length] >= 'a' && hex[length] <= 'f')
			decimal += (hex[length] - 87) * base;
		base *= 16;
		length--;
	}
	return (decimal);
}

void	ft_reset(t_fdf *param)
{
	param->shift_x = WIDTH / 2;
	param->shift_y = HEIGHT / 3;
	param->anglex = 0.8;
	param->angley = 0.8;
	param->zoom = WIDTH / (3 * param->width);
	param->depth = 1;
	param->p = 1;
}

void	ft_free(void **ptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_exit(t_fdf *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win);
	ft_free((void **)param->z_matrix, param->height);
	ft_printf("Good bye... \n");
	exit(0);
}
