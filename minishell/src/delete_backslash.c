#include "minishell.h"

static int	new_len_str(char *str)
{
	int	pos;
	int	len;

	pos = -1;
	len = 0;
	while (str[++pos])
	{
		if (str[pos] != BACKSLASH)
			len++;
	}
	return (len);
}

char *delete (char *str)
{
	int		i;
	int		pos;
	char	*new_str;

	i = 0;
	pos = -1;
	new_str = (char *)malloc(new_len_str(str) + 1);
	if (!new_str)
		return (print_error("translate str", ENO_MEM), NULL);
	while (str[++pos])
	{
		if (str[pos] != BACKSLASH)
		{
			new_str[i] = str[pos];
			i++;
		}
	}
	new_str[i] = '\0';
	return (free(str), new_str);
}

int	iter_node(t_node *node)
{
	int	pos;

	pos = -1;
	node->content->command = delete (node->content->command);
	if (!node->content->command)
		return (0);
	while (node->content->args[++pos])
	{
		node->content->args[pos] = delete (node->content->args[pos]);
		if (!node->content->args[pos])
			return (0);
	}
	return (1);
}

int	delete_backslash(t_node *head)
{
	int	pos;

	pos = -1;
	while (++pos < ft_len_node(head))
	{
		if (!iter_node(&head[pos]))
			return (1);
	}
	return (0);
}
