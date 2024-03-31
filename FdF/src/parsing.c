/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:28:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/25 14:28:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void		ft_check_args(int argc, char **argv);
void		ft_get_dimensions(char *file, t_fdf *fdf);
void		ft_get_map(char *file, t_fdf *fdf);
static void	ft_put_mx(t_dot *vec, char *line, int y, t_fdf *fdf);
static void	ft_fill_mx(t_fdf *fdf, char *file);

void	ft_check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./fdf [map]\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		ft_printf("Too many arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
	{
		ft_printf("%s Invalid file extension\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	ft_printf("Args ✅\n");
}

void	ft_get_dimensions(char *file, t_fdf *fdf)
{
	(*fdf).width = ft_get_width(file);
	(*fdf).height = ft_get_height(file);
}

static void	ft_put_mx(t_dot *vec, char *line, int y, t_fdf *fdf)
{
	char	**num;
	int		x;
	int		k;

	x = -1;
	num = ft_split(line, ' ');
	while (num[++x])
	{
		if (!ft_is_num(num[x]))
			ft_exit(fdf);
		vec[x].z = ft_atoi(num[x]);
		if (fdf->z_max < vec[x].z)
			fdf->z_max = vec[x].z;
		if (fdf->z_min > vec[x].z)
			fdf->z_min = vec[x].z;
		k = 0;
		while (num[x][k] != ',' && num[x][k])
			k++;
		if (num[x][k++] == ',')
			vec[x].color = ft_putnbr_dec(&num[x][k]);
		else
			vec[x].color = ft_atoi("-1");
		free(num[x]);
	}
	free(num);
}

static void	ft_fill_mx(t_fdf *fdf, char *file)
{
	int		fd;
	int		y;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	y = -1;
	while (++y < fdf->height)
	{
		line = get_next_line(fd);
		if (ft_num_words(line, ' ') != fdf->width)
		{
			ft_printf("❌ Invalid map\n");
			ft_exit(fdf);
		}
		if (!line)
			ft_exit(fdf);
		ft_put_mx(fdf->z_matrix[y], line, y, fdf);
		free(line);
	}
	close(fd);
}

void	ft_get_map(char *file, t_fdf *fdf)
{
	int	y;
	int	x;

	y = -1;
	fdf->z_matrix = (t_dot **)malloc(sizeof(t_dot *) * (fdf->height + 1));
	if (!fdf->z_matrix)
		ft_error();
	while (++y < fdf->height)
	{
		fdf->z_matrix[y] = (t_dot *)malloc(sizeof(t_dot) * (fdf->width + 1));
		if (!fdf->z_matrix[y])
			ft_error();
	}
	fdf->z_matrix[y] = NULL;
	ft_fill_mx(fdf, file);
	ft_printf("Map file ✅\n");
}
