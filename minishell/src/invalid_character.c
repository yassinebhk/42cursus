#include "minishell.h"

static int	special_char(char c)
{
	if (c == '&')
		return (1);
	else if (c == ';')
	{
		write(2, &c, 1);
		ft_putstr_fd(": invalid character introduced\n", 2);
		return (2);
	}
	else
		return (0);
}

static int	is_not_meta(int pos, char *line)
{
	if (special_char(line[pos]) == 1)
	{
		if (pos == 0 || line[pos - 1] != '$')
		{
			write(2, &line[pos], 1);
			ft_putstr_fd(": invalid character introduced\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_special_or_meta(int pos, char *line)
{
	if (special_char(line[pos]) == 2 || is_not_meta(pos, line))
		return (1);
	return (0);
}

int	check_consecutive_pipes(int pos, char *line)
{
	int	next_pos;

	if (line[pos] != PIPE)
		return (0);
	next_pos = pos + 1;
	while (line[next_pos] == ' ')
		next_pos++;
	if (line[next_pos] == PIPE)
		return (ft_putstr_fd("Syntax error: unexpected token `|'\n", 2), 1);
	return (0);
}

int	invalid_character(char *line)
{
	int	pos;
	int	single_quote_open;
	int	double_quote_open;

	pos = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while (line[pos] == ' ')
		pos++;
	if (line[pos] == PIPE)
		return (ft_putstr_fd("Syntax error: unexpected token `|'\n", 2), 1);
	while (line[pos])
	{
		if (line[pos] == SINGLE_QUOTE && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (line[pos] == DOUBLE_QUOTE && !single_quote_open)
			double_quote_open = !double_quote_open;
		else if (!single_quote_open && !double_quote_open)
		{
			if (check_special_or_meta(pos, line) || check_consecutive_pipes(pos,
					line))
				return (1);
		}
		pos++;
	}
	return (0);
}
