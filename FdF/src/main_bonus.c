/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/30 14:55:56 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_error(void);
void	ft_init_fdf(t_fdf *fdf);

void	ft_error(void)
{
	exit(EXIT_FAILURE);
}

void	ft_init_fdf(t_fdf *fdf)
{
	(*fdf).mlx_ptr = mlx_init();
	if (!(*fdf).mlx_ptr)
		ft_error();
	(*fdf).win = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (!(*fdf).win)
		ft_error();
	(*fdf).shift_x = WIDTH / 2;
	(*fdf).shift_y = HEIGHT / 3;
	(*fdf).anglex = 0.8;
	(*fdf).angley = 0.8;
	(*fdf).zoom = 5;
	(*fdf).depth = 1;
	(*fdf).p = 1;
	(*fdf).z_max = 0;
	(*fdf).z_min = 0;
	(*fdf).color = 0;
	ft_printf("Initializating the map... 🗺\n");
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_check_args(argc, argv);
	ft_init_fdf(&fdf);
	ft_get_dimensions(argv[1], &fdf);
	ft_get_map(argv[1], &fdf);
	fdf.zoom = WIDTH / (3 * fdf.width);
	fdf.img.img = mlx_new_image(fdf.mlx_ptr, WIDTH, HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel,
			&fdf.img.line_length, &fdf.img.endian);
	ft_draw_line(&fdf);
	ft_printf("Map drawn ✅\n");
	mlx_hook(fdf.win, ON_KEYDOWN, 1L << 0, ft_my_keyhook, &fdf);
	mlx_hook(fdf.win, ON_MOUSEDOWN, 1L << 2, mouse_press, &fdf);
	mlx_hook(fdf.win, ON_DESTROY, 1L << 17, ft_exit, &fdf);
	mlx_loop((fdf).mlx_ptr);
	return (EXIT_SUCCESS);
}
