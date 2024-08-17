/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:08:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 15:33:28 by ybouhaik         ###   ########.fr       */
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

// int	find_node(t_env *env, char *key)
// {
// 	int	pos;
// 	int	len;

// 	pos = -1;
// 	len = ft_lst_size(env);
// 	while (++pos < len)
// 	{
// 		printf("\n%d %d %s %s \n", ft_lst_size(env), ft_strcmp(env[pos].key, key), env[pos].key, key);
// 		if (!ft_strcmp(env[pos].key, key))
// 			return (0);
// 		printf("\n %d %d\n", pos + 1, len);
// 	}
// 	return (1);
// }

void	set_dirs(t_env **env, char *curr, char *old)
{
	t_env	*curr_dir;
	t_env	*old_dir;

	curr_dir = ft_new_node("PWD\0", curr);
	if (!curr_dir)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	if (find_node(*env, "PWD\0"))
		ft_add_back(env, curr_dir);
	old_dir = ft_new_node("OLDPWD\0", old);
	if (!old_dir)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	if (find_node(*env, "OLDPWD\0"))
		ft_add_back(env, old_dir);
}

void	print_list(t_env *env)
{
	while (env)
	{
		printf("%s | %s | %p\n", env->key, env->var, (void *)env->next);
		env = env->next;
	}
	printf("\n---------------------------------\n\n\n\n");
}

t_env	*get_var(char **environment)
{
	int		pos;
	t_env	*env;
	t_env	*new_node;
	char	**split;

	pos = -1;
	env = NULL;
	while (++pos < len_env(environment))
	{
		split = ft_split_mod(environment[pos], '=');
		new_node = ft_new_node(split[0], split[1]);
		ft_add_back(&env, new_node);
		ft_free(split);
	}
	set_dirs(&env, getcwd(NULL, 0), getcwd(NULL, 0));
	print_list(env);
	return (env);
}
