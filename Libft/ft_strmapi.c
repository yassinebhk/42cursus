/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:06 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/09/14 21:49:08 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strmapi (char const *s, char (*f)(unsigned int, char))
{
    char *str;
    unsigned int i;
    
    i = 0;
    str = (char *) malloc ((ft_strlen ((char *)s) + 1) * sizeof (char));
    if (*str)
        return (NULL);
    while (i < ft_strlen ((char *)s))
    {
        *(str + i) = (*f)(i, *(s + i));
        i++;
    }

    *(str + i) = '\0';
    return (str);
}
