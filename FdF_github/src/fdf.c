/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 00:06:41 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	ft_hook(void *param)
{
	(void)param;
}

int	main(int argc, char **argv)
{
	int			i;
    // int         fd;
	mlx_t		*mlx;
	mlx_image_t	*img;

    (void)argc;
    (void)argv;
	i = -1;
    // fd = open(argv[1], O_RDONLY);
    // if (fd < 0)
    //     ft_error();
    
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	while (++i < WIDTH * HEIGHT)
		mlx_put_pixel(img, i % WIDTH, i / WIDTH, BLACK);
    mlx_key_hook(mlx, &ft_my_keyhook, mlx);
    mlx_scroll_hook(mlx, &ft_my_scrollhook, NULL);
    mlx_mouse_hook(mlx, &ft_my_mouse_hook, mlx);
    ft_draw_table(img);
    ft_draw_axis(img);
    //ft_draw_number(img);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
