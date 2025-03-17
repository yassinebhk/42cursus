/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:16:31 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/03/14 13:41:33 by maxgarci         ###   ########.fr       */
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
	int		last_exit_status;
	char	*line;
	t_lists	lists;
	t_node	head;

	last_exit_status = 0;
	line = NULL;
	ft_memset(&lists, 0, sizeof(t_lists));
	lists.env = get_var(environment, 0);
	lists.exp = get_var(environment, 1);
	while (1)
	{
		init_signals();
		line = readline("$ ");
		if (!line)
			signal_d(&head, &lists);
		add_history(line);
		if (line && !is_only_spaces_or_tabs(line))
		{
			last_exit_status = process_command(&head, line, &lists, last_exit_status);
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
