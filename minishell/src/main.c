/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:50:55 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/08/21 22:44:15 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	t_env	*env;
	t_env	*exp;
	char	*line;
	int		status;
	char	**split;

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
			if (status != 42 && status)
				print_error(split[0], status);
			add_history(line);
			ft_free(split);
		}
		free(line);
	}
	rl_clear_history();
	return (free_args(env, exp), 0);
}
