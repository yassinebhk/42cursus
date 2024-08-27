#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	int		status;
	char	*line;
	t_lists	lists;

	status = 0;
	lists.env = get_var(environment, 0);
	lists.exp = get_var(environment, 1);
	while (status != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			status = process_command(line, &lists, environment);
		}
		free(line);
	}
	free(lists.env);
	free(lists.exp);
	rl_clear_history();
	return (0);
}
