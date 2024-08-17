/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:39:40 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 17:48:11 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exp(t_env *env, char *key)
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

void	update_dirs_exp(t_env *exp, char *old_dir, char *new_dir)
{
	while (exp)
	{
		if (!ft_strcmp(exp->key, "declare -x PWD\0"))
			exp->var = new_dir;
		else if (!ft_strcmp(exp->key, "declare -x OLDPWD\0"))
			exp->var = old_dir;
		exp = exp->next;
	}
}

static int	move_to_path_exp(char *new_dir, t_env *exp, char *old_dir)
{
	if (chdir(new_dir))
	{
		perror("cd ");
		return (1);
	}
	update_dirs_exp(exp, old_dir, new_dir);
	return (0);
}

int	cd_exp(char **str, int num_words, t_env *lst)
{
	char *old_dir;
	char *new_dir;

	old_dir = getcwd(NULL, 0);
	if (num_words == 1 || !ft_strcmp(str[1], "~"))
	{
		new_dir = get_exp(lst, "declare -x HOME\0");
		if (!new_dir)
			return (1);
		chdir(new_dir);
		update_dirs_exp(lst, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[1], "..\0"))
	{
		new_dir = get_parent(old_dir);
		chdir(new_dir);
		update_dirs_exp(lst, old_dir, new_dir);
	}
	else if (!ft_strcmp(str[1], "."))
		;
	else
		return (move_to_path_exp(str[1], lst, old_dir));
	return (0);
}
