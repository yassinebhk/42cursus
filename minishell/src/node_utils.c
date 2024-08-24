#include "minishell.h"

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

int	ft_len_node(t_node *head)
{
	int	size;

	size = 0;
	while (head)
	{
		head = head->next;
		size++;
	}
	return (size);
}