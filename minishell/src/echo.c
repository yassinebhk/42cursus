/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:33:33 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/27 12:51:22 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	echo(char **args, int num_args)
{
	int	flag;
	int	pos;

	flag = 0;
	pos = 0;
	while (++pos < num_args && is_valid_arg(args[pos]))
		flag = 1;
	if (pos < num_args)
		printf("%s", args[pos]);
	while (++(pos) < num_args)
		printf(" %s", args[pos]);
	if (!flag)
		printf("\n");
	return (FN_SUCCESS);
}
