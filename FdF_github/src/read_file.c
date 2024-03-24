/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 11:46:48 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int  ft_get_height(char *file)
{
    int     height;
    int     fd;
    char    *line;
    
    height = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        ft_error();
    line = get_next_line(fd);
    while (line)
    {
        height++;
        line = get_next_line(fd);
    }
    close(fd);
    return (height);
}

static int	ft_num_words(char const *s, char c)
{
	int	num;
	int	i;

    printf("%d", 2);
	num = 0;
	i = 0;
	while (s[i])
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

static int  ft_get_width(char *file)
{
    int     width;
    int     fd;
    char    *line;

    width = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        ft_error();
    line = get_next_line(fd);
    printf("Line: %sLA ULTIMA POS DE LINE ESTA MAL", line);
    width = ft_num_words(line, 'c');
    printf("%d", width);
    free(line);
    close(fd);
    return (width);
}

void ft_fill_z(char *buffer, int ***matrix)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (!buffer[k])
    {
        if(buffer[k] == '\n')
        {
            j++;
            i = 0;
        }
        else if (buffer[k] != ' ')
        {
            (*matrix)[i][j] = ft_atoi(&buffer[k]);
            i++;
        }
        k++;
    }
}

static void ft_fill_mx(fdf_t *fdf, char *file)
{
    int fd;
    int bread;
    char *buffer;

    fd = open(file, O_RDONLY);
    if (fd <= 0)
        ft_error();
    buffer = malloc(sizeof(int *) * (*fdf).height * (*fdf).width);
    if (!buffer)
        ft_error();
    bread = read(fd, buffer, (*fdf).height * (*fdf).width);
    if (!bread)
        ft_error();
    ft_fill_z(buffer, &(*fdf).z_matrix);
}


fdf_t   ft_read_file (char *file)
{
    int       i;
    fdf_t   fdf;
    
    i = 0;
    fdf.height = ft_get_height(file);
    fdf.width = ft_get_width(file);
    fdf.z_matrix = malloc(sizeof(int *) * fdf.height);
    if (!fdf.z_matrix)
        ft_error();
    while (fdf.z_matrix[i])
    {
        fdf.z_matrix[i] = malloc(sizeof(int) * fdf.width);
        if (!fdf.z_matrix[i])
            ft_error();
        i++;
    }
    ft_fill_mx(&fdf, file);
    return (fdf);
}

