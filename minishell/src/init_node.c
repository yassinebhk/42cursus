#include "minishell.h"

t_command	*get_content(char *line, int init_pos, int end_pos)
{
	char		*str;
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	str = get_trunc_str(line, init_pos, end_pos);
	if (!str)
		return (free(command), NULL);
	if (!new_command(str, &command))
		return (free(str), free(command), NULL);
	return (free(str), command);
}

t_node	*init_node(char **environment, char *line, int *pos)
{
	int		init_pos;
	t_node	*new_node;

	init_pos = *pos;
	find_pipe(line, pos);
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (print_error("new_node malloc", ENO_MEM), NULL);
	new_node->env = get_var(environment, 0);
	new_node->exp = get_var(environment, 1);
	new_node->error = 0;
	new_node->fd_in = 1;
	new_node->fd_out = 0;
	new_node->next = NULL;
	new_node->content = get_content(line, init_pos, *pos);
	if (!new_node->content)
		return (free(new_node), print_error("new_node content malloc", ENO_MEM),
			NULL);
	return (new_node);
}

int	init_nodes(char **env, char *line, t_node **head)
{
	int		i;
	int		pos;
	t_node	*new_node;

	i = -1;
	pos = 0;
	while (++i <= count_pipes(line))
	{
		new_node = init_node(env, line, &pos);
		if (!new_node)
			return (free_list(*head), 1);
		ft_add_node_back(head, new_node);
		pos++;
	}
	return (0);
}
