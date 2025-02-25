/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:33:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/24 10:22:45 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void clear_spaces(char *str, int *read_pos)
{
	while (ft_isspace(str[*read_pos]))
		++(*read_pos);
}

void	translate_str(char *str)
{
	int		read_pos;
	int		write_pos;
	int		single_quote_open;
	int		double_quote_open;

	read_pos = 0;
	write_pos = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	if (!str)
		return ;
	clear_spaces(str, &read_pos);
	while (str[read_pos])
	{
		str[write_pos++] = str[read_pos];
		check_quotes(str[read_pos], &single_quote_open, &double_quote_open);
		if (ft_isspace(str[read_pos]) && !single_quote_open && !double_quote_open)
			clear_spaces(str, &read_pos);
		else if (str[read_pos] == PIPE && !single_quote_open && !double_quote_open)
		{
			++read_pos;
			clear_spaces(str, &read_pos);
		}
		else
			read_pos++;
	}
	str[write_pos] = '\0';
}
