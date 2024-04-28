/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:16:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 12:16:44 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	leaks(void)
{
	system("leaks push_swap");
}

int main (int argc, char **argv)
{

    if (argc < 2)
        exit(1);
    ft_check_args(argc, argv);
    atexit(leaks);
    return (0);
}
