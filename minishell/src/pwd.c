#include "minishell.h"

int	pwd(t_env *env, t_node **head)
{
	char	*pwd;

	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(NULL), (*head)->error = 1, 1);
	printf("%s\n", pwd);
	free(pwd);
	(*head)->error = 0;
	return (0);
}
