/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/19 21:40:23 by ybouhaik         ###   ########.fr       */
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
		if (line && line[0])
		{
			split = ft_split(line, ' ');
			status = find_built(split, num_words(line, ' '), env, exp);
			if (status == COMMAND_NOT_FOUND)
				print_command_not_found(split[0]);
			ft_free(split);
		}
		free(line);
	}
	free_args(env, exp);
	return (0);
}
