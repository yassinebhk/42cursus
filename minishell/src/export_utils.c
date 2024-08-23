#include "minishell.h"

static int	valid_char(char c, int index)
{
	if (c == '=' && index != 0)
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isdigit(c) && index != 0)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	valid_var(char *var)
{
	int		j;

	j = -1;
	while (var[++j])
	{
		if (!(valid_char(var[j], j)))
			return (1);
	}
	return (0);
}

int	find_eq(char *str)
{
	int	pos;
	int	flag;
	int	cont;

	pos = -1;
	flag = 0;
	cont = 0;
	printf("\nstrr: %s\n", str);
	while (str[++pos])
	{
		if (str[pos] == '=')
			flag++;
		if (flag)
			cont++;
	}
	return (cont);
}

char	*rm_eq(char *str)
{
	int		pos;
	char	*rmv;

	pos = -1;
	rmv = (char *)malloc((ft_strlen(str)) * sizeof(char));
	if (!rmv)
		return (NULL);
	while (++pos < ((int)ft_strlen(str)) - 1)
		rmv[pos] = str[pos];
	rmv[pos] = '\0';
	return (rmv);
}
