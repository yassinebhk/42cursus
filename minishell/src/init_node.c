#include "minishell.h"

t_command	*get_content(char *line, int init_pos, int end_pos)
{
	char		*str;
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	str = get_trunc_str(line, init_pos, end_pos);
	if (!str)
		return (free(command), NULL);
	if (!new_command(str, &command))
		return (free(str), free(command), NULL);
	return (free(str), command);
}

t_env	*ft_nodedup(t_env *node)
{
	t_env	*new_node;

	printf("\n\nholaaaa\n\n");
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (print_error("new_node", ENO_MEM), NULL);
	new_node->index = node->index;
	new_node->key = ft_strdup(node->key);
	new_node->next = NULL;
	if (node->var)
		new_node->var = ft_strdup(node->var);
	else
		new_node->var = NULL;
	return (new_node);
}

t_env	*ft_listdup(t_env *list)
{
	t_env	*new_env;
	t_env	*tmp;

	if (list)
		return (NULL);
	new_env = ft_nodedup(list);
	if (!new_env)
		return (NULL);
	tmp = new_env;
	while (list)
	{
		tmp->next = ft_nodedup(list);
		tmp = tmp->next;
		list = list->next;
	}
	ft_env(new_env);
	printf("\n-------aqui termina new_env-------\n");
	return (new_env);
}

t_node	*fill_node(char *line, int *pos, t_lists *lists)
{
	int		init_pos;
	t_node	*new_node;

	init_pos = *pos;
	find_pipe(line, pos);
	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (print_error("new_node malloc", ENO_MEM), NULL);
	new_node->var_list = (t_lists *)ft_calloc(1, sizeof(t_lists));
	if (!new_node->var_list)
		return (free(new_node), print_error("new_node_var_list malloc",
				ENO_MEM), NULL);
	ft_env(lists->env);
	printf("\n-------aqui termina list-------\n");
	new_node->var_list->env = ft_listdup(lists->env);
	ft_env(new_node->var_list->env);
	printf("\n-------aqui termina node-------\n");
	new_node->var_list->exp = ft_listdup(lists->exp);
	new_node->error = 0;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->next = NULL;
	new_node->content = get_content(line, init_pos, *pos);
	if (!new_node->content)
		return (free_args(new_node->var_list->env, new_node->var_list->exp),
			free(new_node->var_list), free(new_node),
			print_error("new_node content malloc", ENO_MEM), NULL);
	return (new_node);
}

int	fill_nodes(char *line, t_node **head, t_lists *lists)
{
	int		i;
	int		pos;
	t_node	*new_node;

	i = -1;
	pos = 0;
	while (++i <= count_pipes(line))
	{
		new_node = fill_node(line, &pos, lists);
		if (!new_node)
			return (free_list(*head), *head = NULL, 1);
		ft_env(new_node->var_list->env);
		ft_add_node_back(head, new_node);
		pos++;
	}
	return (0);
}
