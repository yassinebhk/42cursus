#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	char	*line;
	int		status;

	status = 0;
	while (status != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			status = process_command(environment, line);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
