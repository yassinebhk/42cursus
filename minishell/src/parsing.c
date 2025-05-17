/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:34:08 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/05/17 19:41:31 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotes(const char *line, int *single_quote_count,
		int *double_quote_count)
{
	int	pos;
	int	single_quote_open;
	int	double_quote_open;

	pos = -1;
	single_quote_open = 0;
	double_quote_open = 0;
	*single_quote_count = 0;
	*double_quote_count = 0;
	while (line[++pos])
	{
		if (line[pos] == SINGLE_QUOTE && !double_quote_open)
		{
			single_quote_open = !single_quote_open;
			(*single_quote_count)++;
		}
		else if (line[pos] == DOUBLE_QUOTE && !single_quote_open)
		{
			double_quote_open = !double_quote_open;
			(*double_quote_count)++;
		}
	}
	*single_quote_count = single_quote_open;
	*double_quote_count = double_quote_open;
}

int	check_quotes_balance(int single_quote_count, int double_quote_count)
{
	if (single_quote_count % 2 != 0)
	{
		ft_putstr_fd(SINGLE_QUOTE_ERROR, 2);
		return (0);
	}
	if (double_quote_count % 2 != 0)
	{
		ft_putstr_fd(DOUBLE_QUOTE_ERROR, 2);
		return (0);
	}
	return (1);
}

int	even_quotes(char *line)
{
	int	s_quotes;
	int	d_quotes;

	count_quotes(line, &s_quotes, &d_quotes);
	return (check_quotes_balance(s_quotes, d_quotes));
}
