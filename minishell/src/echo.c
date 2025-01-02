#include "minishell.h"

static int	is_valid_arg(char *str)
{
	int	pos;

	pos = 0;
	if (str[pos] != '-')
		return (0);
	while (str[++pos])
	{
		if (str[pos] != 'n')
			return (0);
	}
	return (1);
}

int	echo(char **str, int pos, int num_words, t_node **head)
{
	int	flag;

	flag = 0;
	while (++pos < num_words && is_valid_arg(str[pos]))
		flag = 1;
	if (flag)
	{
		if (pos < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
	}
	else
	{
		if (pos < num_words)
			printf("%s", str[pos]);
		while (++(pos) < num_words)
			printf(" %s", str[pos]);
		printf("\n");
	}
	(*head)->error = 0;
	return (0);
}
