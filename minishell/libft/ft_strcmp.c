/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:42:30 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/07/12 17:26:10 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	diff;

	diff = 0;
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		diff = *s1 - *s2;
	return (diff);
}
/*#include <stdio.h>

int main (void)
{
	char s1 [] = "hola";
	char s2 [] = "holb";
	int dif = ft_strcmp(s1,s2);
	printf ("diferencia:%d", dif);
	return (0);
}*/
