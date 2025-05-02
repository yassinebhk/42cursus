/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:11 by maxgarci          #+#    #+#             */
/*   Updated: 2025/05/02 16:37:37 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_command_executable(t_node *head)
{
	if (!access((head)->content->command, e_X_OK))
		return (YES);
	return (NO);
}

static int	print_command_not_found(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (COMMAND_NOT_FOUND);
}

static int	try_absolute_paths(char **split, char *command, t_node *head)
{
	int		pos;
	char	*tmp;
	char	*absolute_dir;

	pos = -1;
	while (split[++pos])
	{
		tmp = ft_strjoin(split[pos], "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
			return (free(head->content->command),
				head->content->command = ft_strdup(absolute_dir),
				ft_free(split), free(tmp), free(absolute_dir), FN_SUCCESS);
		free(tmp);
		free(absolute_dir);
	}
	return (FN_FAILURE);
}

int	get_absolute_path(char *path_list, char *command, t_node *head)
{
	char	**split;
	int		result;

	if (is_command_executable(head))
		return (FN_SUCCESS);
	if (!path_list)
		return (print_command_not_found(command));
	split = ft_split(path_list, ':');
	if (!split)
		return (print_command_not_found(command));
	result = try_absolute_paths(split, command, head);
	if (result == FN_SUCCESS)
		return (FN_SUCCESS);
	ft_free(split);
	return (print_command_not_found(command));
}
