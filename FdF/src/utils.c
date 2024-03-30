/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 11:46:48 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		ft_get_height(char *file);
int		ft_get_width(char *file);
int		ft_num_words(char const *s, char c);
int		ft_is_num(char *str);
float	ft_angle(float ang, float value);

int	ft_get_height(char *file)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

int	ft_get_width(char *file)
{
	int		width;
	int		fd;
	char	*line;

	width = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	line = get_next_line(fd);
	width = ft_num_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	ft_num_words(char const *s, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != c)
		{
			num++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	return (num);
}

float	ft_angle(float ang, float value)
{
	ang += value;
	if (ang < 0)
		ang = M_2PI + ang;
	if (ang >= M_2PI)
		ang = ang - M_2PI;
	return (ang);
}

int	ft_is_num(char *str)
{
	int	i;
	int	has_a_num;

	has_a_num = 0;
	i = 0;
	if (str[i] == '\n')
		has_a_num = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_a_num = 1;
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' '
			&& str[i] != '-' && !ft_is_hex(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	if (!has_a_num)
		return (0);
	return (1);
}
