/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:53:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/20 12:56:30 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_command(char *line, t_lists *lists, int last_status)
{
	t_node	*head;
	int		status;

	head = NULL;
	status = -1;
	if (!line || !even_quotes(line) || invalid_character(line))
		return (FN_FAILURE);
	translate_str(line);
	if (fill_nodes(line, &head, lists, last_status))
		return (free_node(head), free(line), FN_FAILURE);
	if (head->content->command)
		g_signal = 1;
	if (expand_commands(&head))
		return (free_node(head), free(line), FN_FAILURE);
	if (ft_len_node(head) == 1)
		status = execute_one_command(&head, lists);
	else
		status = execute_commands(&head, lists);
	return (free_node(head), free(line), status);
}
