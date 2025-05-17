/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:27:52 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/17 19:29:54 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_str(t_node *tmp, char *str, int last_status)
{
	int		pos;
	int		quotes;
	char	*new_arg;

	pos = -1;
	quotes = 0;
	new_arg = ft_strdup("");
	while (str[++pos])
	{
		if (!quotes && str[pos] == SINGLE_QUOTE)
			quotes = 1;
		else if (!quotes && str[pos] == DOUBLE_QUOTE)
			quotes = 2;
		else if (quotes == 1 && str[pos] == SINGLE_QUOTE)
			quotes = 0;
		else if (quotes == 2 && str[pos] == DOUBLE_QUOTE)
			quotes = 0;
		else if ((!quotes || quotes == 2) && str[pos] == DOLLAR
			&& (!ft_isspace(str[pos + 1]) && str[pos + 1] != DOUBLE_QUOTE))
			new_arg = load_variable(tmp, (char *[]){str, new_arg}, last_status,
					&pos);
		else
			new_arg = strjoin_char(new_arg, str[pos]);
	}
	return (new_arg);
}
