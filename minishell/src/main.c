#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	int		status_code;
	char	*line;
	t_lists	lists;

	status_code = 0;
	ft_memset(&lists, 0, sizeof(t_lists));
	lists.env = get_var(environment, 0);
	lists.exp = get_var(environment, 1);
	while (status_code != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			status_code = process_command(line, &lists);
		}
		free(line);
	}
	free_args(lists.env, lists.exp);
	rl_clear_history();
	return (0);
}
