#include "minishell.h"

static int	is_special_char(char c)
{
	return (!isalnum((unsigned char)c) && c != BACKSLASH && c != SINGLE_QUOTE
		&& c != DOUBLE_QUOTE);
}

static void	process_char(char c, int *single_quote_open, int *double_quote_open,
		char *new_str, int *i)
{
	if (c == SINGLE_QUOTE && !(*double_quote_open))
		*single_quote_open = !(*single_quote_open);
	else if (c == DOUBLE_QUOTE && !(*single_quote_open))
		*double_quote_open = !(*double_quote_open);
	else
	{
		if (*single_quote_open || *double_quote_open)
		{
			if (is_special_char(c) || c == BACKSLASH)
				new_str[(*i)++] = BACKSLASH;
		}
		new_str[(*i)++] = c;
	}
}

static int	new_len_str(const char *str)
{
	int	pos;
	int	len;
	int	single_quote_open;
	int	double_quote_open;

	pos = 0;
	len = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while (str[pos])
	{
		if (str[pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (str[pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		len++;
		if (single_quote_open || double_quote_open)
		{
			if (is_special_char(str[pos]) || str[pos] == BACKSLASH)
				len++;
		}
		pos++;
	}
	return (len);
}

char	*translate_str(char *str)
{
	int		i;
	int		pos;
	int		single_quote_open;
	int		double_quote_open;
	char	*new_str;

	i = 0;
	pos = -1;
	single_quote_open = 0;
	double_quote_open = 0;
	new_str = (char *)malloc(new_len_str(str) + 1);
	if (!new_str)
		return (print_error("translate str", ENO_MEM), NULL);
	while (str[++pos])
	{
		process_char(str[pos], &single_quote_open, &double_quote_open, new_str,
			&i);
	}
	new_str[i] = '\0';
	return (new_str);
}

int	translate_args(t_node *node)
{
	int	pos;

	pos = -1;
	node->content->command = translate_str(node->content->command);
	if (!node->content->command)
		return (0);
	while (++pos < node->content->num_args)
	{
		node->content->args[pos] = translate_str(node->content->args[pos]);
		if (!node->content->args[pos])
			return (0);
	}
	return (1);
}
