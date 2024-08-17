/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:23:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 17:47:26 by ybouhaik         ###   ########.fr       */
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
			env->var = new_dir;
		else if (!ft_strcmp(env->key, "OLDPWD\0"))
			env->var = old_dir;
		env = env->next;
	}
}

static int	move_to_path_env(char *new_dir, t_env *env, char *old_dir)
{
	if (chdir(new_dir))
	{
		perror("cd ");
		return (1);
	}
	update_dirs_env(env, old_dir, new_dir);
	return (0);
}

int	cd_env(char **str, int num_words, t_env *lst)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (num_words == 1 || !ft_strcmp(str[1], "~"))
	{
		new_dir = get_env(lst, "HOME\0");
		if (!new_dir)
			return (1);
		chdir(new_dir);
		update_dirs_env(lst, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[1], "..\0"))
	{
		new_dir = get_parent(old_dir);
		chdir(new_dir);
		update_dirs_env(lst, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[1], "."))
		;
	else
		return (move_to_path_env(str[1], lst, old_dir));
	return (0);
}

int	cd(char **str, int num_words, t_env *env, t_env *exp)
{
	if (cd_env(str, num_words, env) || cd_exp(str, num_words, exp))
		return (1);
	return (0);
}
