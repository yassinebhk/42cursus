/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:49:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/03/24 00:34:17 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// static void	ft_hook(void *param)
// {
// 	(void)param;
// }

void write_matrix(fdf_t fdf)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < fdf.width)
    {   
        j = 0;
        while(j < fdf.height)
        {
            printf("%d ", fdf.z_matrix[i][j]);
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    
    fdf_t   fdf;
    
    if (argc < 2)
        ft_error();
    fdf = ft_read_file(argv[1]);
    write_matrix(fdf);
    return (EXIT_SUCCESS);

}