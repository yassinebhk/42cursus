#include "minishell.h"

int	split_by_spaces(char *line, t_env *env, t_env *exp)
{
	int		status;
	char	**split;

	split = ft_split(line, ' ');
	status = find_built(split, num_words(line, ' '), env, exp);
	if (status)
		print_error(split[0], status);
	ft_free(split);
	return (status);
}
