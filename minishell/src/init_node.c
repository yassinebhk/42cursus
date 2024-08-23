#include "minishell.h"

//tnatos nodos como count_pipes() haya
//splitear por | reales
//luego en cada nodo splitear por espacios y transcribir

static t_node	*ft_last_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_node_back(t_node **head, t_env *new_node)
{
	t_env	*last;

	if (!new_node)
	{
		print_error("ft_add_back", ENO_MEM);
		return ;
	}
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_last(*head);
		if (last)
			last->next = new_node;
	}
}

// t_env	*ft_add_node(char *key, char *arg, int flag)
// {
// 	t_env	*node;
// 	char	*tmp;

// 	node = (t_env *)malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->next = NULL;
// 	tmp = ft_strjoin(arg, "\"");
// 	if (flag == 0)
// 	{
// 		node->key = ft_strdup(key);
// 		if (!arg)
// 			node->var = NULL;
// 		else
// 			node->var = ft_strdup(arg);
// 	}
// 	else
// 	{
// 		node->key = ft_strjoin("declare -x ", key);
// 		if (!arg)
// 			node->var = NULL;
// 		else
// 			node->var = ft_strjoin("\"", tmp);
// 	}
// 	return (free(tmp), node);
// }

void	find_backslash(char *line, int *pos)
{
	while(line[*pos] && (*pos) != BACKSLASH)
		(*pos)++;
	return (pos);
}

t_command	*get_content(char *line, int init_pos, int end_pos)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	// command->args = 
	// command->command = 
	// command->num_args = 
	return (command);
}

t_node	*init_node(char **environment, char *line, int *pos)
{
	int		init_pos;
	t_node	*new_node;
	
	init_pos = *pos;
	find_backslash(line, &pos);
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (print_error("new_node malloc", ENO_MEM), NULL);
	new_node->env = get_var(environment, 0);
	new_node->exp = get_var(environment, 1);
	new_node->error = 0;
	new_node->fd_in = 0;
	new_node->fd_out = 0;
	new_node->content = get_content(line, init_pos, *pos);
	return (new_node);

}

int	init_nodes(char **env, char *line, t_node **head)
{
	int		i;
	int		pos;
	t_node	*new_node;

	i = -1;
	pos = 0;
	while(++i <= count_pipes(line))
	{
		new_node = init_node(env, line, &pos);
		if (!new_node)
			return (1);
		ft_add_node_back(head, new_node);
	}
	return (0);
}