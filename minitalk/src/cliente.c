/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliente.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:20:32 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/01 14:20:33 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cliente.h"

int main()
{
    //printf("Hello, World!\n");
    ft_printf("Hello, World!\n");
    
    while (get_next_line(0))
    {
        ft_printf("%s", get_next_line(0));
        get_next_line(0);
    }
    return 0;
}
