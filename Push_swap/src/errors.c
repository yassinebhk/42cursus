/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:34:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 12:34:24 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void ft_exit()
{
    ft_printf("Error\n");
    exit(1);
}

void ft_exit_str(char *str, int flag)
{
    if (flag)
        free(str);
    ft_printf("Error\n");
    exit(1);
}

void ft_exit_mtx(char **mtx)
{
    while (mtx)
    {
        free(*mtx);
        mtx++;
    }
    free(mtx);
    ft_printf("Error\n");
    exit(1);
}
