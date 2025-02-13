/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:30:18 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/13 10:41:55 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == SINGLE_QUOTE && !(*double_quote))
		*single_quote = !(*single_quote);
	if (c == DOUBLE_QUOTE && !(*single_quote))
		*double_quote = !(*double_quote);
}

int	count_pipes(char *line)
{
	int	pos;
	int	single_quote;
	int	double_quote;
	int	num_pipes;

	pos = -1;
	single_quote = 0;
	double_quote = 0;
	num_pipes = 0;
	while (line[++pos])
	{
		check_quotes(line[pos], &single_quote, &double_quote);
		if (line[pos] == BACKSLASH)
		{
			pos++;
			continue ;
		}
		if (line[pos] == PIPE && !single_quote && !double_quote)
			num_pipes++;
	}
	return (num_pipes);
}
