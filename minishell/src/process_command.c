#include "minishell.h"

static int	setup_and_validate(t_node **head, char *line, t_lists *lists,
		int exit_code)
{
	if (!even_quotes(line) || invalid_character(line))
		return (free_list(*head), 1);
	line = translate_str(line);
	if (fill_nodes(line, head, lists, exit_code))
		return (free(line), free_list(*head), 1);
	free(line);
	if ((*head)->content->command)
		g_signal = 1;
	if (expand_commands(head))
		return (free_list(*head), 1);
	if (delete_backslash(head))
		return (EXIT_FAILURE);
	return (0);
}

static int	execute_and_restore(t_node *head, t_lists *lists, int saved_stdin,
		int saved_stdout)
{
	int	status;

	if (ft_len_node(head) == 1)
		status = execute_one_command(&head, lists);
	else
		status = execute_commands(&head, lists);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (free_list(head), perror("Failed to restore stdin"),
			EXIT_FAILURE);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (free_list(head), perror("Failed to restore stdout"),
			EXIT_FAILURE);
	return (free_list(head), status);
}

int	process_command(t_node *head, char *line, t_lists *lists, int exit_code)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_and_validate(&head, line, lists, exit_code))
		return (1);
	return (execute_and_restore(head, lists, saved_stdin, saved_stdout));
}
