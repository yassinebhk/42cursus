/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:41:09 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/02/25 17:53:12 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/ft_printf/ft_printf.h"
# include "../libs/get_next_line/get_next_line.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

# define WIDTH 2280
# define HEIGHT 1800
# define BUFF_SIZE 4096
# define MENU_WIDTH 300
# define MENU_HEIGTH 500
# define BUF_SIZE 2048
# define M_2PI 6.28318530718
# define M_PI_6 0.52359877559
# define M_PI_3 1.0471975512
# define MAX_COLOR_HEX 16777215

# define WHITE 0xffffff
# define BLACK 0x000000
# define DARK_BLUE 0x00008B
# define LIGHT_BLUE 0xADD8E6
# define DARK_GREEN 0x006400
# define TURQUOISE 0x07EDED
# define PINK 0xE5037E
# define GREY 0xbebebe
# define LIGHT_GREY 0xd3d3d3
# define DARK_GREY 0xa9a9a9
# define BLUE 0xff0000
# define BLUE_SEA 0x2196f3
# define CYAN 0xffff
# define GREEN_1 0xff00
# define GREEN_LAND 0x0b6730
# define YELLOW 0xffff00
# define GOLD 0xffd700
# define RED 0xff0000
# define SILVER 0xc0c0c0
# define MAROON 0x800000
# define NAVY 0x000080
# define OLIVE 0x808000
# define TEAL 0x008080
# define LIME 0x00ff00
# define INDIGO 0x4b0082
# define VIOLET 0xee82ee
# define ORANGE 0xffa500
# define PURPLE 0x800080
# define BROWN 0xa52a2a
# define BROWN_LAND 0xa39791
# define DARK_BROWN 0x5A4309
# define GREEN_2 0x006400
# define WHITE_LAND 0xC4BDAC
# define WHITE_SEA 0x00FFFF
# define WHITE_MOUNTAIN 0x808080

typedef struct dot
{
	int		z;
	int		color;
}			t_dot;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct fdf
{
	void	*mlx_ptr;
	void	*win;
	int		height;
	int		width;
	int		z_max;
	int		z_min;
	float	x;
	float	x1;
	float	y;
	float	y1;
	int		zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	int		p;
	float	anglex;
	float	angley;
	int		depth;
	t_img	img;
	t_dot	**z_matrix;
}			t_fdf;

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/*******************************************/
/*                                         */
/*                 DRAW                    */
/*                                         */
/*******************************************/

t_fdf		ft_read_file(char *file);
void		ft_draw_line(t_fdf *fdf);

/*******************************************/
/*                                         */
/*                 HOOKS                   */
/*                                         */
/*******************************************/

int			mouse_press(int button, int x, int y, t_fdf *data);
int			ft_my_keyhook(int keydata, t_fdf *param);
void		ft_error(void);
void		ft_check_args(int argc, char **argv);
void		ft_get_dimensions(char *file, t_fdf *fdf);
int			ft_get_width(char *file);
int			ft_get_height(char *file);
int			ft_num_words(char const *s, char c);
void		ft_get_map(char *file, t_fdf *fdf);
void		ft_menu(t_fdf *data);
void		ft_isometric(float *x, float *y, int z, t_fdf *fdf);
void		ft_scale(t_fdf *fdf);
void		ft_bressenham(int x1, int y1, int x2, int y2, t_fdf *fdf);
int			ft_get_color(t_fdf *fdf, int x, int y);
void		ft_exit(t_fdf *param);
float		ft_angle(float ang, float value);
int			ft_is_num(char *str);
int			ft_is_hex(char c);
int			ft_putnbr_dec(char *hex);
void		ft_change_color(t_fdf *param);
int			projection(int a);
void		ft_reset(t_fdf *param);

#endif
