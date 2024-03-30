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

int			ft_z(t_dot dot, int z, int mid_z, int len);
void		ft_change_color(t_fdf *param);
void		ft_choose_color(t_dot *dot, int mode);
void		ft_draw_line(t_fdf *fdf);
static int	gradient(int start, int end, int len, int pix);

void	ft_change_color(t_fdf *param)
{
	param->color += 1;
	if (param->color > 2)
		param->color = 0;
}

static int	gradient(int start, int end, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((end >> 16) - (start >> 16)) / (double)len;
	increment[1] = (double)(((end >> 8) & 0xFF) - ((start >> 8) & 0xFF))
		/ (double)len;
	increment[2] = (double)((end & 0xFF) - (start & 0xFF)) / (double)len;
	new[0] = (start >> 16) + ft_round(pix * increment[0]);
	new[1] = ((start >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (start & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}

int	ft_z(t_dot dot, int z, int mid_z, int len)
{
	if (z > mid_z)
		return (gradient(dot.color_2, dot.color_3, len, z));
	else
		return (gradient(dot.color_1, dot.color_2, len, z));
}

void	ft_choose_color(t_dot *dot, int mode)
{
	if (mode == 0)
	{
		dot->color_1 = BLUE_SEA;
		dot->color_2 = BROWN_LAND;
		dot->color_3 = GREEN_LAND;
	}
	else if (mode == 1)
	{
		dot->color_1 = WHITE;
		dot->color_2 = PINK;
		dot->color_3 = PURPLE;
	}
	else if (mode == 2)
	{
		dot->color_1 = NAVY;
		dot->color_2 = VIOLET;
		dot->color_3 = GOLD;
	}
}

void	ft_draw_line(t_fdf *fdf)
{
	t_pos	pos1;
	t_pos	pos2;

	pos1.y = -1;
	while (++pos1.y < (*fdf).height)
	{
		pos1.x = 0;
		while (pos1.x < (*fdf).width)
		{
			if (pos1.x < (*fdf).width - 1)
			{
				pos2.x = pos1.x + 1;
				pos2.y = pos1.y;
				ft_bressenham(pos1, pos2, fdf);
			}
			if (pos1.y < (*fdf).height - 1)
			{
				pos2.x = pos1.x;
				pos2.y = pos1.y + 1;
				ft_bressenham(pos1, pos2, fdf);
			}
			pos1.x++;
		}
	}
	ft_menu(fdf);
}
