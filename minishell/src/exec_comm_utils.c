/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comm_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:05:41 by maxgarci          #+#    #+#             */
/*   Updated: 2025/04/20 14:07:15 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path_list(char *command, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(command, env->key))
			return (env->var);
		env = env->next;
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("path variable not found at env.\n", 2);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (FN_FAILURE);
	return (FN_SUCCESS);
}

int	get_absolute_path(char *path_list, char *command, t_node *head)
{
	int		pos;
	char	*tmp;
	char	**split;
	char	*path;
	char	*absolute_dir;

	if (!access((head)->content->command, X_OK))
		return (FN_SUCCESS);
	pos = -1;
	split = ft_split(path_list, ':');
	while (split[++pos])
	{
		path = split[pos];
		tmp = ft_strjoin(path, "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
			return (free(head->content->command),
				head->content->command = ft_strdup(absolute_dir),
				ft_free(split), free(tmp), free(absolute_dir), FN_SUCCESS);
		free(tmp);
		free(absolute_dir);
	}
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (ft_free(split), FN_FAILURE);
}
