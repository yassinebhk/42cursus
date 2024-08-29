#include "minishell.h"

void	count_quotes(const char *line, int *single_quote_count,
		int *double_quote_count)
{
	int	pos;
	int	single_quote_open;
	int	double_quote_open;

	pos = -1;
	single_quote_open = 0;
	double_quote_open = 0;
	*single_quote_count = 0;
	*double_quote_count = 0;
	while (line[++pos])
	{
		if (line[pos] == SINGLE_QUOTE && !double_quote_open)
		{
			single_quote_open = !single_quote_open;
			(*single_quote_count)++;
		}
		else if (line[pos] == DOUBLE_QUOTE && !single_quote_open)
		{
			double_quote_open = !double_quote_open;
			(*double_quote_count)++;
		}
	}
	*single_quote_count = single_quote_open;
	*double_quote_count = double_quote_open;
}

int	check_quotes_balance(int single_quote_count, int double_quote_count)
{
	if (single_quote_count % 2 != 0)
	{
		ft_putstr_fd(SINGLE_QUOTE_ERROR, 2);
		return (0);
	}
	if (double_quote_count % 2 != 0)
	{
		ft_putstr_fd(DOUBLE_QUOTE_ERROR, 2);
		return (0);
	}
	return (1);
}

int	even_quotes(char *line)
{
	int	single_quote_count;
	int	double_quote_count;

	count_quotes(line, &single_quote_count, &double_quote_count);
	if (!check_quotes_balance(single_quote_count, double_quote_count))
	{
		return (0);
	}
	return (1);
}
