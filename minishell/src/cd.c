/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:23:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 21:11:03 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->var);
		env = env->next;
	}
	printf("\n❌ Error: no %s key was found.\n\n", key);
	return (NULL);
}

void	update_dirs_env(t_env *env, char *old_dir, char *new_dir)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD\0"))
		{
			free(env->var);
			env->var = ft_strdup(new_dir);
		}
		else if (!ft_strcmp(env->key, "OLDPWD\0"))
		{
			free(env->var);
			env->var = ft_strdup(old_dir);
			free(old_dir);
		}
		env = env->next;
	}
}

static int	move_to_path_env(char *new_dir, t_env *env, t_env *exp,
		char *old_dir)
{
	char	*new_rel_dir;
	char	*tmp;
	char	*cwd;

	tmp = ft_strjoin("/", new_dir);
	cwd = getcwd(NULL, 0);
	new_rel_dir = ft_strjoin(cwd, tmp);
	if (new_dir && *new_dir == '/' && chdir(new_dir))
	{
		perror("cd absolute ");
		return (free(new_rel_dir), 1);
	}
	else if (*new_dir != '/' && chdir(new_rel_dir))
	{
		perror("cd relative ");
		return (free(new_rel_dir), 1);
	}
	if (*new_dir == '/')
	{
		update_dirs_env(env, old_dir, new_dir);
		update_dirs_env(exp, old_dir, new_dir);
	}
	else
	{
		update_dirs_env(env, old_dir, new_rel_dir);
		update_dirs_env(exp, old_dir, new_rel_dir);
	}
	return (free(cwd), free(tmp), free(new_rel_dir), 0);
}

int	cd_env(char **str, int num_words, t_env *env, t_env *exp)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (num_words == 1 || !ft_strcmp(str[1], "~"))
	{
		new_dir = get_env(env, "HOME\0");
		if (!new_dir)
			return (1);
		chdir(new_dir);
		update_dirs_env(env, old_dir, new_dir);
		update_dirs_env(exp, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[1], "..\0"))
	{
		new_dir = get_parent(old_dir);
		chdir(new_dir);
		update_dirs_env(env, old_dir, new_dir);
		update_dirs_env(exp, old_dir, new_dir);
		free(new_dir);
	}
	else if (!ft_strcmp(str[1], "."))
		free(old_dir);
	else
		return (move_to_path_env(str[1], env, exp, old_dir));
	return (0);
}

int	cd(char **str, int num_words, t_env *env, t_env *exp)
{
	if (cd_env(str, num_words, env, exp))
		return (1);
	return (0);
}
