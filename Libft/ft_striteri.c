/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:25 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:49:27 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_striteri (char *s, void (*f)(unsigned int, char*))
{
    char *str;
    unsigned int i;
    
    i = 0;
    while (*(s + i) != '\0')
    {
        (*f)(i, (s + i));
        i++;
    }
}

