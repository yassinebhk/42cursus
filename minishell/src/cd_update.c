/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:14:42 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/20 13:15:20 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_dirs(t_env *list, char *old_dir, char *new_dir)
{
	while (list)
	{
		if (!ft_strcmp(list->key, "PWD\0"))
		{
			free(list->var);
			list->var = ft_strdup(new_dir);
		}
		else if (!ft_strcmp(list->key, "OLDPWD\0"))
		{
			free(list->var);
			list->var = ft_strdup(old_dir);
			free(old_dir);
		}
		list = list->next;
	}
}

void	update(t_env *env, t_env *exp, char *old_dir, char *new_dir)
{
	update_dirs(env, old_dir, new_dir);
	update_dirs(exp, old_dir, new_dir);
}