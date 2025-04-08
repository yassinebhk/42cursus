/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:53:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/22 14:33:21 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_command(t_node *head, char *line, t_lists *lists)
{
	int	status;

	status = -1;
	if (!line || !even_quotes(line) || invalid_character(line))
		return (free_list(head), FN_FAILURE);
	translate_str(line);
	if (fill_nodes(line, &head, lists))
		return (free_list(head), FN_FAILURE);
	if (head->content->command)
		g_signal = 1;
	if (expand_commands(&head))
		return (free_list(head), FN_FAILURE);
	/*if (delete_backslash(&head))*/
	/*	return (EXIT_FAILURE);*/
	if (ft_len_node(head) == 1)
		status = execute_one_command(&head, lists);
	else
		status = execute_commands(&head, lists);
	return (free_list(head), status);
}
