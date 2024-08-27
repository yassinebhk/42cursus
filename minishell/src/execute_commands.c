#include "minishell.h"

int	execute_commands(t_node **head)
{
	(void)head;
	// int	pid;
	// int	fd[2];
	// int	*pipes;

	// if(delete_backslash(head))
	// 	return (1);
	// while(head)
	// {
	// 	pid = fork();
	// 	init_pipes(pipes);
	// 	if (pid < 0)
	// 	{
	// 		ft_putstr_fd("fork failed", 2);
	// 		return (1);
	// 	}
	// 	else if(!pid)
	// 		execute_child(head);
	// 	else
	// 	{
	// 		close(pipes);
	// 		waitpid(-1, NULL, 0);
	// 	}
	// 	head = head->next;
	// }
	// return (free_list(head), 0);
	return (0);
}

// AL FINALIZAR CADA HIJO LIBERAR LA MEMORIA DE CAD APROGRAMA