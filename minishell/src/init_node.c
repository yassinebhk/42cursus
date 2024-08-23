#include "minishell.h"

// tnatos nodos como count_pipes() haya
// splitear por | reales
// luego en cada nodo splitear por espacios y transcribir

static t_node	*ft_last_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_node_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!new_node)
	{
		print_error("ft_add_back", ENO_MEM);
		return ;
	}
	if (!*head)
		*head = new_node;
	else
	{
		last = ft_last_node(*head);
		if (last)
			last->next = new_node;
	}
}

void	find_pipe(char *line, int *pos)
{
	int	single_quote_open;
	int	double_quote_open;

	single_quote_open = 0;
	double_quote_open = 0;
	while (line[*pos])
	{
		if (line[*pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (line[*pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		else if (line[*pos] == PIPE && !single_quote_open && !double_quote_open)
			break ;
		(*pos)++;
	}
}

char	*get_trunc_str(char *line, int init_pos, int end_pos)
{
	int		pos;
	char	*str;

	pos = 0;
	str = (char *)malloc(end_pos - init_pos);
	if (!str)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	while (init_pos < end_pos)
	{
		str[pos] = line[init_pos];
		pos++;
		init_pos++;
	}
	str[pos] = '\0';
	return (str);
}

int	split_str(char *str, t_command **command)
{
	int		pos;
	char	**split;

	pos = -1;
	split = ft_split(str, ' ');
	if (!split || !split[0])
		return (0);
	(*command)->num_args = num_words(str, ' ') - 1;
	(*command)->command = ft_strdup(split[0]);
	(*command)->args = (char **)malloc(sizeof(char *) * ((*command)->num_args
				+ 1));
	if (!(*command)->args)
		return (ft_free(split), 0);
	while (++pos < (*command)->num_args)
		(*command)->args[pos] = ft_strdup(split[pos + 1]);
	(*command)->args[pos] = NULL;
	ft_free(split);
	return (1);
}

t_command	*get_content(char *line, int init_pos, int end_pos)
{
	char		*str;
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (print_error("new_command malloc", ENO_MEM), NULL);
	str = get_trunc_str(line, init_pos, end_pos);
	if (!str)
		return (NULL);
	// cuando liberar esto? al final? no se cuantos nodos habrán. Por el null puede diferenciar para liberar o no
	if (!split_str(str, &command))
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
	new_node->fd_in = 0;
	new_node->fd_out = 0;
	new_node->next = NULL;
	new_node->content = get_content(line, init_pos, *pos);
	if (!new_node->content)
		return (free(new_node), NULL);
	return (new_node);
}

int	init_nodes(char **env, char *line, t_node **head)
{
	int i;
	int pos;
	t_node *new_node;

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