#include "minishell.h"

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
	int		status;
	char	*line;
	t_lists	lists;
	t_node	head;

	ft_memset(&lists, 0, sizeof(t_lists));
	status = 0;
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
			status = process_command(&head, line, &lists, status);
			g_signal = 0;
		}
	}
	free_args(lists.env, lists.exp);
	rl_clear_history();
	return (0);
}

// guaradr el status con el wait: wifeexit wexitstatus
