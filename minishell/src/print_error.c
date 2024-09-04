#include "minishell.h"

void	print_error(char *command, int error)
{
	if (error == ENO_MEM)
		ft_putstr_fd(" allocation failed, no memory available: ", 2);
	if (error == PARSING)
		ft_putstr_fd(" parsing failed", 2);
	if (error == BAD_ASSIGNMENT)
		ft_putstr_fd(" bad assignment: ", 2);
	if (error == COMMAND_NOT_FOUND)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putchar_fd('\n', 2);
}
