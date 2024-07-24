/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:34:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/07/24 19:42:57 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	ft_exit_str(int *str)
{
	free(str);
	write(2, "Error\n", 6);
	exit(1);
}

void	ft_exit_mtx(char **mtx)
{
	while (mtx)
	{
		free(*mtx);
		mtx++;
	}
	free(mtx);
	write(2, "Error\n", 6);
	exit(1);
}

void	ft_exit_str_and_mtx(int *str, char **mtx, int pos)
{
	free(str);
	while (mtx[pos])
	{
		free(mtx[pos]);
		pos++;
	}
	free(mtx);
	write(2, "Error\n", 6);
	exit(1);
}
