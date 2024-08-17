/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/17 17:50:39 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environment)
{
	t_env	*env;
	t_env	*exp;
	char	*line;
	char	**split;

	(void)argc;
	(void)argv;
	env = get_var(environment, 0);
	exp = get_var(environment, 1);
	while (1)
	{
		line = readline("$ ");
		if (!line)
			;
		else
		{
			split = ft_split(line, ' ');
			find_built(split, num_words(line, ' '), env, exp);
			free(split);
		}
	}
	free_args(line, env, exp);
	return (0);
}
