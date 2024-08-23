#include "minishell.h"

int	process_command(char **env, char *line)
{
	t_node *head;

	head = NULL;
	if (!even_quotes(line) || invalid_character(line) && init_nodes(env, line,
			&head))
		return (1);
}