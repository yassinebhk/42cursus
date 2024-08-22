#include "minishell.h"

int	split_by_spaces(char *line, t_env *env, t_env *exp)
{
	int		status;
	char	**split;

	split = ft_split(line, ' ');
	status = find_built(split, num_words(line, ' '), env, exp);
	if (status == COMMAND_NOT_FOUND)
		print_command_not_found(split[0]);
	ft_free(split);
	return (status);
}
