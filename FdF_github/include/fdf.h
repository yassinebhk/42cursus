/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:41:09 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 00:38:28 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
//# include "MLX42_Int.h"
# include "MLX42_Input.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFF_SIZE 4096

# define WHITE 0xffffffff
# define BLACK 0x00000000
# define GREY 0xbebebeff
# define BLUE 0xff0000ff
# define CYAN 0xffff
# define GREEN 0xff00
# define YELLOW 0xffff00
# define GOLD 0xffd700
# define RED 0xff0000

# define BUF_SIZE 2048
# define M_PI_6 0.52359877559
# define M_PI_3 1.0471975512

typedef struct fdf
{
	int width;
	int height;
	int **z_matrix;

	void *mlx_ptr;
	void *win_ptr;
}			fdf_t;


/*******************************************/
/*                                         */
/*                 MATH                    */
/*                                         */
/*******************************************/
/*
		M_LOG2E         log2(e)
		M_LOG10E        log10(e)
		M_LN2           ln(2)
		M_LN10          ln(10)
		M_PI            pi
		M_PI_2          pi / 2
		M_PI_4          pi / 4
		M_1_PI          1 / pi
		M_2_PI          2 / pi
		M_2_SQRTPI      2 / sqrt(pi)
		M_SQRT2         sqrt(2)
		M_SQRT1_2       sqrt(1/2)

		These return a remainder of the division of x by y with an integral quotient.  remquo() additionally provides access to a few lower bits of the quotient.  They are correctly rounded.

		double fdim(double, double)
		double fmax(double, double)
		double fmin(double, double)

		fmax(x, y) and fmin(x, y) return the maximum and minimum of x and y,
			respectively.  fdim(x,
			y) returns the positive difference of x and y. All are correctly rounded.

		double fma(double x, double y, double z)

		fma(x, y, z) computes the value (x*y)
			+ z as though without intermediate rounding.  It is correctly rounded.

		double fabs(double)
		double sqrt(double)
		double cbrt(double)
		double hypot(double, double)

		fabs(x), sqrt(x), and cbrt(x) return the absolute value, square root,
			and cube root of x, respectively.  hypot(x, y) returns sqrt(x*x
			+ y*y).  fabs() and sqrt() are correctly rounded.

		double exp(double)
		double exp2(double)
		double __exp10(double)
		double expm1(double)

		exp(x), exp2(x), __exp10(x), and expm1(x) return e**x, 2**x, 10**x,
			and e**x - 1, respectively.

		double log(double)
		double log2(double)
		double log10(double)
		double log1p(double)

		log(x), log2(x), and log10(x) return the natural, base-2,
			and base-10 logarithms of x,
			respectively.  log1p(x) returns the natural log of 1+x.

		double logb(double)
		int ilogb(double)

		logb(x) and ilogb(x) return the exponent of x.

		double modf(double, double *)
		double frexp(double, int *)

		modf(x,
			&y) returns the fractional part of x and stores the integral part in y.  frexp(x,
			&n) returns the mantissa of x and stores the exponent in n. They are correctly rounded.

		double ldexp(double, int)
		double scalbn(double, int)
		double scalbln(double, long int)

		ldexp(x, n), scalbn(x, n), and scalbln(x,
			n) return x*2**n.  They are correctly rounded.

		double pow(double, double)

		pow(x,y) returns x raised to the power y.

		double cos(double)
		double sin(double)
		double tan(double)

		cos(x), sin(x), and tan(x) return the cosine, sine and tangent of x,
			respectively.  Note that x is interpreted as specifying an angle in radians.
*/

typedef struct line_ecuation
{
	double	m;
	double	n;
}	line_t;

/*******************************************/
/*                                         */
/*                 DRAW                    */
/*                                         */
/*******************************************/

fdf_t   ft_read_file (char *file);
void	ft_draw_table(mlx_image_t *img);
void	ft_draw_x(mlx_image_t *img, int i, int j, int jmax);
void	ft_draw_y(mlx_image_t *img, int i, int imax, int j);
void	ft_draw_number(mlx_image_t *img);
void    ft_draw_axis(mlx_image_t *img);
line_t  ft_line_ec(double x1, double y1, double x2, double y2);

/*******************************************/
/*                                         */
/*                 HOOKS                   */
/*                                         */
/*******************************************/

void	ft_my_keyhook(mlx_key_data_t keydata, void *param);
void	ft_my_scrollhook(double xdelta, double ydelta, void *param);
void	ft_my_mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, mlx_t *param1);


void	ft_error(void);


#endif
