/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:17:46 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/04/27 13:17:47 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

long	ft_atoi_mod(const char *nptr, int *error)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
    *error = 0;
	while (ft_isspace(nptr[i]))
		++i;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	num = 0;
	while (ft_isdigit(nptr[i]))
	{
        *error= 1;
		num *= 10;
		num += nptr[i] - '0';
		++i;
	}
	return ((num * sign));
}

char	*ft_strjoin_mod(char const *s1, char const *s2, int mlc)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (*(s1 + i) != '\0')
	{
		*(s + i) = *(s1 + i);
		i++;
	}
	*(s + i) = '\0';
	s = ft_strcat(s, (char *)s2);
    if (mlc)
	    free((char *)s1);
	return (s);
}
