#include "minishell.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	t_env	*env;
	t_env	*exp;
	char	*line;
	int		status;
	//int		num_pipes;

	status = 0;
	env = get_var(environment, 0);
	exp = get_var(environment, 1);
	while (status != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			if (!even_quotes(line))
			{
				count_pipes(line);
				status = split_by_spaces(line, env, exp);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (free_args(env, exp), 0);
}
