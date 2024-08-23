#include "minishell.h"

int	is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static int	new_len_str(const char *str)
{
	int	pos;
	int	new_len;
	int	single_quote_open;
	int	double_quote_open;

	pos = 0;
	new_len = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while (str[pos])
	{
		if (str[pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (str[pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		else
		{
			if (single_quote_open || double_quote_open)
				new_len++;
			new_len++;
		}
		pos++;
	}
	return (new_len);
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
			new_str[(*i)++] = BACKSLACH;
		new_str[(*i)++] = c;
	}
}

char	*translate_str(const char *str)
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
		process_char(str[pos], &single_quote_open, &double_quote_open, new_str,
			&i);
	new_str[i] = '\0';
	return (new_str);
}
