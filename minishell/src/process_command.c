#include "minishell.h"

void	print_list(t_node *head)
{
	int	i;

	while (head)
	{
		if (head->content)
		{
			printf("\n%d|%s|", head->content->num_args, head->content->command);
			if (head->content->args)
			{
				i = -1;
				if (head->content->args[++i])
					printf("%s", head->content->args[i]);
				while (head->content->args[i])
				{
					printf(" %s", head->content->args[i]);
					i++;
				}
			}
			printf("\n");
		}
		head = head->next;
	}
}

int	process_command(char **env, char *line)
{
	t_node *head;

	head = NULL;
	if (!even_quotes(line) || invalid_character(line) || init_nodes(env, line,
			&head))
		return (1);
	print_list(head);
	return (free_list(head), 0);
}