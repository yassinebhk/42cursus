/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:23:15 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 16:42:00 by ybouhaik         ###   ########.fr       */
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

void	update_dirs(t_env *env, char *old_dir, char *new_dir)
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

void	print_listt(t_env *env)
{
	while (env)
	{
		printf("%s = %s\n", env->key, env->var);
		env = env->next;
	}
	printf("\n---------------------------------\n\n\n\n");
}

static int	move_to_path(char *new_dir, t_env *env, char *old_dir)
{
	if (chdir(new_dir))
	{
		perror("cd ");
		return (1);
	}
	update_dirs(env, old_dir, new_dir);
	return (0);
}

static char	*get_parent(char *dir)
{
	int		i;
	int		slash;
	char	*path;

	i = -1;
	while (dir[++i])
	{
		if (dir[i] == '/' && dir[i + 1])
			slash = i;
	}
	path = (char *)malloc((slash + 1) * sizeof(char));
	if (!path)
		return (NULL);
	if (slash == 0)
	{
		path[0] = '/';
		path[1] = '\0';
		return (path);
	}
	i = -1;
	while (++i < slash)
		path[i] = dir[i];
	path[i] = '\0';
	return (path);
}

int	cd(char **str, int pos, int num_words, t_env *env)
{
	char	*old_dir;
	char	*new_dir;

	old_dir = getcwd(NULL, 0);
	if (num_words == 1 || !ft_strcmp(str[pos + 1], "~"))
	{
		new_dir = get_env(env, "HOME\0");
		if (!new_dir)
			return (1);
		chdir(new_dir);
		update_dirs(env, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[pos + 1], "..\0"))
	{
		new_dir = get_parent(old_dir);
		chdir(new_dir);
		update_dirs(env, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[pos + 1], "."))
		;
	else
		return (move_to_path(str[pos + 1], env, old_dir));
	// print_listt(env);
	return (0);
}
