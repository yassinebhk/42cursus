/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:08:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:23 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(char **environment)
{
	int	len;

	len = 0;
	while (environment[len])
		len++;
	return (len);
}

int	find_node(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (0);
		env = env->next;
	}
	return (1);
}
void	set_dirs_env(t_env **env, char *curr, char *old)
{
	t_env	*curr_dir;
	t_env	*old_dir;

	if (find_node(*env, "PWD\0"))
	{
		curr_dir = ft_new_node("PWD\0", curr, 0);
		if (!curr_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(env, curr_dir);
	}
	else if (find_node(*env, "OLDPWD\0"))
	{
		old_dir = ft_new_node("OLDPWD\0", old, 0);
		if (!old_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(env, old_dir);
	}
	free(curr);
	free(old);
}

// void	set_dirs_env(t_env **env, char *curr, char *old)
// {
// 	t_env	*curr_dir;
// 	t_env	*old_dir;

// 	curr_dir = ft_new_node("PWD\0", curr, 0);
// 	if (!curr_dir)
// 	{
// 		free(curr);
// 		free(old);
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (find_node(*env, "PWD\0"))
// 		ft_add_back(env, curr_dir);
// 	old_dir = ft_new_node("OLDPWD\0", old, 0);
// 	if (!old_dir)
// 	{
// 		free(curr);
// 		free(old);
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (find_node(*env, "OLDPWD\0"))
// 		ft_add_back(env, old_dir);
// 	free(curr);
// 	free(old);
// }

// void	set_dirs_exp(t_env **exp, char *curr, char *old)
// {
// 	t_env	*curr_dir;
// 	t_env	*old_dir;

// 	curr_dir = ft_new_node("declare -x PWD\0", curr, 0);
// 	if (!curr_dir)
// 	{
// 		perror("malloc failed");
// 		free(curr);
// 		free(old);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (find_node(*exp, "declare -x PWD\0"))
// 		ft_add_back(exp, curr_dir);
// 	old_dir = ft_new_node("declare -x OLDPWD\0", old, 0);
// 	if (!old_dir)
// 	{
// 		perror("malloc failed");
// 		free(curr);
// 		free(old);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (find_node(*exp, "declare -x OLDPWD\0"))
// 		ft_add_back(exp, old_dir);
// 	free(curr);
// 	free(old);
// }

void	set_dirs_exp(t_env **exp, char *curr, char *old)
{
	t_env	*curr_dir;
	t_env	*old_dir;

	if (find_node(*exp, "declare -x PWD\0"))
	{
		curr_dir = ft_new_node("declare -x PWD\0", curr, 0);
		if (!curr_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(exp, curr_dir);
	}
	else if (find_node(*exp, "declare -x OLDPWD\0"))
	{
		old_dir = ft_new_node("declare -x OLDPWD\0", old, 0);
		if (!old_dir)
		{
			free(curr);
			free(old);
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		ft_add_back(exp, old_dir);
	}
	free(curr);
	free(old);
}

t_env	*get_var(char **environment, int flag)
{
	int		pos;
	t_env	*env;
	char	**split;
	t_env	*new_node;

	pos = -1;
	env = NULL;
	while (++pos < len_env(environment))
	{
		split = ft_split_mod(environment[pos], '=');
		new_node = ft_new_node(split[0], split[1], flag);
		ft_add_back(&env, new_node);
		ft_free(split);
	}
	if (!flag)
		set_dirs_env(&env, getcwd(NULL, 0), getcwd(NULL, 0));
	else
		set_dirs_exp(&env, getcwd(NULL, 0), getcwd(NULL, 0));
	return (env);
}
