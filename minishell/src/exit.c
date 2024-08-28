#include "minishell.h"

int	ft_exit(char **str)
{
	printf("exit\n");
	(void)str;
	//exit + arg, ese aegumento es el valor que debe devolver exit
	return (42);
}
