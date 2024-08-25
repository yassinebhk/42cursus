#include "minishell.h"

// void	print_list(t_node *head)
// {
// 	int	i;

// 	while (head)
// 	{
// 		if (head->content)
// 		{
// 			printf("\n%d|%s|", head->content->num_args, head->content->command);
// 			if (head->content->args)
// 			{
// 				i = 0;
// 				if (head->content->args[i])
// 				{
// 					printf("%s", head->content->args[i]);
// 					i++;
// 				}
// 				while (head->content->args[i])
// 				{
// 					printf(" %s", head->content->args[i]);
// 					i++;
// 				}
// 			}
// 			printf("\n");
// 		}
// 		head = head->next;
// 	}
// 	printf("----------------------------------\n");
// }

void print_redir(t_redir *redir) {
    while (redir) {
        printf("    Redirection type: %d\n", redir->type);
        printf("    Valid: %d\n", redir->valid);
        printf("    Filename: %s\n", redir->filename);
		printf("\n punteros %p %p\n", redir, redir->next);
        redir = redir->next;
    }
}

void print_command(t_command *cmd) {
    if (!cmd) {
        printf("    (null)\n");
        return;
    }
    printf("  Command: %s\n", cmd->command);
    printf("  Number of arguments: %d\n", cmd->num_args);
    if (cmd->args) {
        printf("  Arguments:\n");
        for (int i = 0; i < cmd->num_args; i++) {
            printf("    arg[%d]: %s\n", i, cmd->args[i]);
        }
    } else {
        printf("  No arguments.\n");
    }

    if (cmd->redir) {
        printf("  Redirections:\n");
        print_redir(cmd->redir);
    } else {
        printf("  No redirections.\n");
    }
}

void print_list(t_node *node) {
    int node_count = 0;
    while (node)
	{
        printf("       Command content     \n");
        print_command(node->content);

        // Print additional fields (env, exp) if necessary
        // ...

        printf("\n");
        node = node->next;
        node_count++;
    }
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
	print_list(head);
	while (++pos < ft_len_node(head))
	{
		// if (!translate_args(&head[pos]))
		// 	return (free_list(head), 1);
	}
	//print_list(head);
	// if (ft_len_node(head) == 1 && excute_one_command(head))
	// 	return (free_list(head), 1);
	// else if (execute_commands(head))
	// 	return (free_list(head), 1);
	return (free_list(head), 0);
}
