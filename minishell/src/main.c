/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 15:49:15 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	ft_env(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	unset(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (1);
}

int	export(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (0);
}

// int	pwd(char **str, int pos, int num_words, char **env)
// {

// 	return (0);
// }

int	main(int argc, char **argv, char **environment)
{
	t_env	*env;
	char	*line;
	char	**split;

	(void)argc;
	(void)argv;
	env = get_var(environment);
	while (1)
	{
		line = readline("$ ");
		if (!line)
			;
		else
		{
			split = ft_split(line, ' ');
			find_built(split, num_words(line, ' '), env);
			free(split);
		}
	}
	free_args(line, env, len_env(environment));
	return (0);
}
