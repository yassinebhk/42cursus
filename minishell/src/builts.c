#include "minishell.h"

int	find_built(char **str, int num_words, t_lists **lists, t_node **head)
{
	if (!ft_strcmp(str[0], "echo"))
		return (echo(str, 0, num_words, head));
	else if (!ft_strcmp(str[0], "cd"))
		return (cd(str, num_words, lists, head));
	else if (!ft_strcmp(str[0], "pwd"))
		return (pwd((*lists)->env, head));
	else if (!ft_strcmp(str[0], "export"))
		return (export(str, num_words, lists, head));
	else if (!ft_strcmp(str[0], "unset"))
		return (unset(str, num_words, lists, head));
	else if (!ft_strcmp(str[0], "env"))
		return (ft_env((*lists)->env, head));
	else
		return (ft_exit(str, &(*lists)->env, &(*lists)->exp, head));
	return (0);
}
