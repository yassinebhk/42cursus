#include "minishell.h"

extern int				g_signal;

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	char	*line;
	t_lists	lists;
	t_node	head;

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
		if (line[0])
		{
			process_command(&head, line, &lists);
			//free(line);
			g_signal = 0;
		}
	}
	free_args(lists.env, lists.exp);
	rl_clear_history();
	return (0);
}

// guaradr el status con el wait: wifeexit wexitstatus
