/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:01:36 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/17 20:03:21 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_argument(char *str, int *read_pos)
{
	int	squote_opened;
	int	dquote_opened;
	int	in_quotes;

	squote_opened = 0;
	dquote_opened = 0;
	in_quotes = 0;
	while ((str[*read_pos] && !ft_isspace(str[*read_pos]) && !is_redir(str,
				*read_pos)) || squote_opened || dquote_opened)
	{
		if (!in_quotes && (squote_opened || dquote_opened))
			in_quotes = 1;
		check_quotes(str[*read_pos], &squote_opened, &dquote_opened);
		++(*read_pos);
	}
}

int	skip_redir_token(char *str, int pos)
{
	while (is_redir(str, pos))
		pos++;
	while (ft_isspace(str[pos]))
		pos++;
	return (pos);
}

int	skip_redir_filename(char *str, int pos)
{
	int	quotes;

	quotes = 0;
	while (str[pos] > ' ' || quotes)
	{
		if (str[pos] == SINGLE_QUOTE && quotes == 1)
			quotes = 0;
		else if (str[pos] == SINGLE_QUOTE && quotes == 0)
			quotes = 1;
		else if (str[pos] == DOUBLE_QUOTE && quotes == 2)
			quotes = 0;
		else if (str[pos] == DOUBLE_QUOTE && quotes == 0)
			quotes = 2;
		pos++;
	}
	return (pos);
}
