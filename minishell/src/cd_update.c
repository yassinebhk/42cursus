/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:32:23 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 11:32:30 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_dirs_env(t_env **list, char *old_dir, char *new_dir)
{
	t_env	*tmp;
	char	*copy;

	tmp = *list;
	copy = ft_strdup(new_dir);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD\0"))
		{
			if (tmp->var)
				free(tmp->var);
			tmp->var = ft_strdup(copy);
		}
		else if (!ft_strcmp(tmp->key, "OLDPWD\0"))
		{
			if (tmp->var)
				free(tmp->var);
			tmp->var = ft_strdup(old_dir);
		}
		tmp = tmp->next;
	}
	free(copy);
}

static void	update_dirs_exp(t_env **list, char *old_dir, char *new_dir)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "declare -x PWD\0"))
		{
			if (tmp->var)
				free(tmp->var);
			tmp->var = ft_strdup(new_dir);
		}
		else if (!ft_strcmp(tmp->key, "declare -x OLDPWD\0"))
		{
			if (tmp->var)
				free(tmp->var);
			tmp->var = ft_strdup(old_dir);
			free(old_dir);
		}
		tmp = tmp->next;
	}
}

void	update(t_env **env, t_env **exp, char *old_dir, char *new_dir)
{
	char	*copy;

	copy = ft_strdup(new_dir);
	update_dirs_env(env, old_dir, new_dir);
	update_dirs_exp(exp, old_dir, copy);
	free(copy);
}
