/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:21:05 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/18 21:01:02 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_arg(char *str)
{
	int	pos;

	pos = 0;
	if (str[pos] != '-')
		return (0);
	while (str[++pos])
	{
		if (str[pos] != 'n')
			return (0);
	}
	return (1);
}

int	echo(char **str, int pos, int num_words)
{
	int	flag;

	flag = 0;
	while (++pos < num_words && is_valid_arg(str[pos]))
		flag = 1;
	if (flag)
	{
		if (pos < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
	}
	else
	{
		if (pos < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
		printf("\n");
	}
	return (0);
}
