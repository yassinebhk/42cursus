#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	t_env	*env;
	t_env	*exp;
	char	*line;
	char	*quoted_line;
	int		status;

	status = 0;
	while (status != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);

				quoted_line = translate_str(line);
				printf("\n%s <---> %s\n", line, quoted_line);
				status = split_by_spaces(quoted_line, env, exp);
				free(quoted_line);

		}
		free(line);
	}
	rl_clear_history();
	return (free_args(env, exp), 0);
}
