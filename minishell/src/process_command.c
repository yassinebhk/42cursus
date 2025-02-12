/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:53:34 by ybouhaik          #+#    #+#             */
/*   Updated: 2025/02/09 15:46:15 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_redir(t_redir redir)
{
	printf("    Redirection type: %d\n", redir.type);
	printf("    Valid: %d\n", redir.valid);
	printf("    Filename: %s. (%ld)\n", redir.filename,
		ft_strlen(redir.filename));
}

void	print_command(t_command *cmd)
{
	if (!cmd)
	{
		printf("    (null)\n");
		return ;
	}
	printf("  Command: %s\n", cmd->command);
	printf("  Number of arguments: %d\n", cmd->num_args);
	if (cmd->num_args > 0 && cmd->args)
	{
		printf("  Arguments:\n");
		for (int i = 0; i < cmd->num_args; i++)
			printf("    arg[%d]: %s. (%ld)\n", i, cmd->args[i],
				ft_strlen(cmd->args[i]));
	}
	else
	{
		printf("  No arguments.\n");
	}
	printf("  Number of redirs: %d\n", cmd->num_redir);
	if (cmd->num_redir && cmd->redir)
	{
		printf("  Redirections:\n");
		for (int i = 0; i < cmd->num_redir; i++)
			print_redir(cmd->redir[i]);
	}
	else
		printf("  No redirections.\n");
}

void	print_list(t_node *node)
{
	int	node_count;

	node_count = 0;
	while (node)
	{
		printf("       Command content     \n");
		print_command(node->content);
		printf("  fd:\n");
		// Print additional fields (env, exp) if necessary
		// ...
		printf("    fd_in: %d\n", node->fd_in);
		printf("    fd_out: %d\n", node->fd_out);
		node = node->next;
		node_count++;
	}
	printf("\n-----------------------------------------------\n");
}

int	process_command(t_node *head, char *line, t_lists *lists, int exit_code)
{
	int	status;

	status = -1;
	head = NULL;
	if (!even_quotes(line) || invalid_character(line))
		return (free_list(head), 1);
	translate_str(line);
	if (fill_nodes(line, &head, lists, exit_code))
		return (free(line), free_list(head), 1);
	free(line);
	if (head->content->command)
		g_signal = 1;
	if (expand_commands(&head))
		return (free_list(head), 1);
	/*if (delete_backslash(&head))*/
	/*	return (EXIT_FAILURE);*/
	if (ft_len_node(head) == 1)
		status = execute_one_command(&head, lists);
	else
		status = execute_commands(&head, lists);
	return (free_list(head), status);
}
