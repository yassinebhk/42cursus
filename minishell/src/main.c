/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:16:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/04/09 12:48:07 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

extern int	g_signal;

int	is_only_spaces_or_tabs(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (!ft_isspace(line[pos]))
			return (0);
		pos++;
	}
	return (1);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	char	*line;
	t_lists	lists;
	t_node	head;

	line = NULL;
	ft_memset(&lists, 0, sizeof(t_lists));
	lists.env = get_var(environment, 0);
	lists.exp = get_var(environment, 1);
	head.last_status = 0;
	while (1)
	{
		init_signals();
		line = readline("$ ");
		if (!line)
			signal_d(&head, &lists);
		add_history(line);
		if (line && !is_only_spaces_or_tabs(line))
		{
			head.last_status = process_command(&head, line, &lists);
			g_signal = 0;
			free(line);
			line = NULL;
		}
	}
	free_lists(lists.env, lists.exp);
	rl_clear_history();
	return (0);
}

// guardar el status con el wait: wifeexit wexitstatus
