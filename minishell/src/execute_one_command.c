/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:09:37 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 14:20:59 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_one_command(t_node **head, t_lists *lists)
{
	char	*path_list;

	if (is_built_in((*head)->content->command))
		return (execute_built(head, lists));
	path_list = get_path_list("PATH\0", lists->env);
	if (!path_list)
		return (VARIABLE_NOT_FOUND);
	if (get_absolute_path(path_list, (*head)->content->command, *head))
		return (COMMAND_NOT_FOUND);
	if (redirect(*head))
		return (FN_FAILURE);
	return (FN_SUCCESS);
}
