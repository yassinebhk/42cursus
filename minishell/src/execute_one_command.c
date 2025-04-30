/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:09:37 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/29 10:47:04 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_one_command(t_node **head, t_lists *lists)
{
	char	*path_list;
	int		status;

	status = FN_SUCCESS;
	if ((*head)->content->command && access((*head)->content->command, e_X_OK))
	{
		if (is_built_in((*head)->content->command))
			return (execute_built(head, lists));
		path_list = get_path_list("PATH\0", lists->env);
		status = get_absolute_path(path_list, (*head)->content->command, *head);
	}
	if (status == FN_SUCCESS)
		return (redirect(*head));
	else
		return (status);
}
