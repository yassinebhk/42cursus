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
	printf("\n");
}

int	process_command(char **env, char *line)
{
	int		pos;
	t_node	*head;

	pos = -1;
	head = NULL;
	if (!even_quotes(line) || invalid_character(line) || init_nodes(env, line,
			&head))
		return (1);
	// print_list(head);
	while (++pos < ft_len_node(head))
	{
		if (!translate_args(&head[pos]))
			return (free_list(head), 1);
	}
	if (ft_len_node(head) == 1)
	{
		if (excute_one_command(head))
			return (free_list(head), 1);
	}
	else
	{
		if (execute_commands(head))
			// en los hijos liberar la memoria de todo el programa
			return (free_list(head), 1);
	}
	return (free_list(head), 0);
}
