/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:11:51 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/17 20:15:01 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str, int pos)
{
	return ((str[pos] == '>' && str[pos + 1] == '>') || str[pos] == '>'
		|| (str[pos] == '<' && str[pos + 1] == '<') || str[pos] == '<');
}
