/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/18 21:31:40 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environment)
{
	t_env	*env;
	t_env	*exp;
	char	*line;
	int		status;
	char	**split;

	(void)argc;
	(void)argv;
	status = 0;
	env = get_var(environment, 0);
	exp = get_var(environment, 1);
	while (status != 42)
	{
		line = readline("$ ");
		if (line)
		{
			split = ft_split(line, ' ');
			status = find_built(split, num_words(line, ' '), env, exp);
			ft_free(split);
		}
		free(line);
	}
	free_args(line, env, exp);
	return (0);
}
