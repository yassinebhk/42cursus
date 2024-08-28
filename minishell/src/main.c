#include "minishell.h"

// void	init(t_node **head, t_lists *lists)
// {
// 	(*head) = (t_node *)malloc(sizeof(t_node));
// 	if (!(*head))
// 		return (print_error("(*head) malloc", ENO_MEM), NULL);
// 	(*head)->var_list->env = lists->env;
// 	(*head)->var_list->exp = lists->exp;
// 	(*head)->error = 0;
// 	(*head)->fd_in = 1;
// 	(*head)->fd_out = 0;
// 	(*head)->next = NULL;
// 	(*head)->content = NULL;;
// }

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **environment)
{
	int		status_code;
	char	*line;
	t_lists	lists;

	status_code = 0;
	ft_memset(&lists, 0, sizeof(t_lists));
	lists.env = get_var(environment, 0);
	lists.exp = get_var(environment, 1);
	// init(&head, environment);
	while (status_code != 42)
	{
		line = readline("$ ");
		if (line && line[0])
		{
			add_history(line);
			status_code = process_command(line, &lists);
		}
		free(line);
	}
	free_args(lists.env, lists.exp);
	rl_clear_history();
	return (0);
}
