/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:30:24 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/05/13 20:47:12 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->var);
		env = env->next;
	}
	printf("\nError: no %s key was found.\n\n", key);
	return (NULL);
}

static int	move_to_path_env(char *new_dir, t_env **env, t_env **exp)
{
	char	*new_rel_dir;
	char	*tmp;
	char	*cwd;
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	tmp = ft_strjoin("/", new_dir);
	cwd = getcwd(NULL, 0);
	new_rel_dir = ft_strjoin(cwd, tmp);
	if (new_dir && *new_dir == '/' && chdir(new_dir))
	{
		ft_putstr_fd("cd absolute\n", 2);
		return (free(old_dir), free(new_rel_dir), free(cwd), free(tmp), 1);
	}
	else if (*new_dir != '/' && chdir(new_rel_dir))
	{
		ft_putstr_fd("cd relative\n", 2);
		return (free(old_dir), free(new_rel_dir), free(cwd), free(tmp), 1);
	}
	if (*new_dir == '/')
		update(env, exp, old_dir, new_dir);
	else
		update(env, exp, old_dir, new_rel_dir);
	return (free(cwd), free(tmp), free(new_rel_dir), 0);
}

static int	change_directory(t_env **env, t_env **exp, char *var, int flag)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (flag)
	{
		new_dir = get_env(*env, var);
		if (!new_dir)
			return (free(old_dir), 1);
	}
	else
		new_dir = get_parent(old_dir);
	if (chdir(new_dir))
	{
		ft_putstr_fd(old_dir, 2);
		ft_putstr_fd(" parent does not exist:\n", 2);
		if (!flag)
			free(new_dir);
		return (free(old_dir), 1);
	}
	update(env, exp, old_dir, new_dir);
	if (!flag)
		free(new_dir);
	return (0);
}

int	cd_env(char **args, int num_args, t_lists **lists)
{
	if (num_args > 2)
		return (ft_putstr_fd(" too many arguments", 2), 1);
	if (num_args == 1 || !ft_strcmp(args[1], "~\0"))
	{
		if (change_directory(&(*lists)->env, &(*lists)->exp, "HOME\0", 1))
			return (free(NULL), CANNOT_CHANGE_DIR);
	}
	else if (!ft_strcmp(args[1], "..\0"))
	{
		if (change_directory(&(*lists)->env, &(*lists)->exp, NULL, 0))
			return (free(NULL), CANNOT_CHANGE_DIR);
	}
	else if (!ft_strcmp(args[1], "-\0"))
	{
		if (change_directory(&(*lists)->env, &(*lists)->exp, "OLDPWD\0", 1))
			return (free(NULL), CANNOT_CHANGE_DIR);
	}
	else if (ft_strcmp(args[1], ".\0"))
		return (move_to_path_env(args[1], &(*lists)->env, &(*lists)->exp));
	return (0);
}

int	cd(char **args, int num_args, t_lists **lists)
{
	if (cd_env(args, num_args, lists))
		return (free(NULL), 1);
	return (free(NULL), 0);
}
