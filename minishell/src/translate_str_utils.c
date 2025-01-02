#include "minishell.h"

static int	is_special_char(char c)
{
	return (!isalnum((unsigned char)c) && !isspace((unsigned char)c));
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
		if (*single_quote_open)
		{
			if (is_special_char(c))
				new_str[(*i)++] = BACKSLASH;
		}
		else if (*double_quote_open)
		{
			if (is_special_char(c) && c != DOLLAR)
				new_str[(*i)++] = BACKSLASH;
		}
		new_str[(*i)++] = c;
	}
}
