/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:48:18 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/21 23:15:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	even_quotes(char *line)
{
	int	pos;
	int	single_quote;
	int	double_quote;

	pos = -1;
	single_quote = 0;
	double_quote = 0;
	while (line[++pos])
	{
		if (line[pos] == SINGLE_QUOTE)
			single_quote++;
		else if (line[pos] == DOUBLE_QUOTE)
			double_quote++;
	}
	if (single_quote % 2 != 0)
	{
		ft_putstr_fd(SINGLE_QUOTE_ERROR, 2);
		return (1);
	}
	else if (double_quote % 2 != 0)
	{
		ft_putstr_fd(DOUBLE_QUOTE_ERROR, 2);
		return (1);
	}
	return (0);
}
