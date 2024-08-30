#include "minishell.h"

int	init_pipes(int **pipes, t_node *head)
{
	int	i;
	int	pos;
	int	fd[2];

	i = -1;
	pos = 0;
	*pipes = (int *)malloc(2 * sizeof(int) * (ft_len_node(head) - 1));
	if (!(*pipes))
		return (print_error("pipe array malloc ", ENO_MEM), 0);
	while (++i < ft_len_node(head) - 1)
	{
		if (pipe(fd) == -1)
			return (ft_putstr_fd("pipe function failed", 2), 0);
		pipes[0][pos++] = fd[0];
		pipes[0][pos++] = fd[1];
	}
	return (1);
}

void	close_pipes(int *pipes, int len)
{
	int	i;

	i = -1;
	while (++i < 2 * (len - 1))
		close(pipes[i]);
}

/**
 * @brief El proposito de esta funcion es cerrar los fds abiertos
 * cuando se sobreescriba ese tipo de redireccion.
 * Se ignora si es correcta la logica
 */
int	ft_open(char *file, int flag, int old_fd)
{
	if (old_fd > 2)
		close(old_fd);
	return (open(file, flag));
}

int heredoc(void)
{
	return (1);
}

/**
enum	e_redirtype
{
	r_output = 1,
	r_append = 2,
	r_input = 3,
	r_heredoc = 4
};
*/
int	open_and_get_fd(t_node *tmp, int i, int *fd_in, int *fd_out)
{
	int		redir;
	char	*file;

	redir = tmp->content->redir[i].type;
	file = tmp->content->redir[i].filename;
	if (redir == 1)
		*fd_out = ft_open(file, O_CREAT | O_WRONLY, tmp->fd_out);
	else if (redir == 2)
		*fd_out = ft_open(file, O_CREAT | O_APPEND | O_WRONLY, tmp->fd_out);
	else if (redir == 3)
		*fd_in = ft_open(file, O_RDONLY, tmp->fd_in);
	else if (redir == 4)
		*fd_in = heredoc();
	// hay que hacer el heredoc antes de pasar al siguiente (foto)
	if (*fd_in == -1 || *fd_out == -1)
	{
		ft_putstr_fd("Error opening ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}

int	set_fd(t_node **head)
{
	int		i;
	int		fd_out;
	int		fd_in;
	t_node	*tmp;

	i = -1;
	tmp = *head;
	while (tmp)
	{
		fd_out = -42;
		fd_in = -42;
		while (++i < tmp->content->num_redir)
		{
			if (!open_and_get_fd(tmp, i, &fd_out, &fd_in))
				return (0);
		}
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
	return (1);
}

void	ft_dup2(int *fd_in, int *fd_out)
{
	//hacer una copia temporal para restaurar (0 y 1) para la siguiente linea
	dup2(*fd_in, 0);
	dup2(*fd_out, 1);
	close(*fd_in);
	close(*fd_out);
}

void	execute_child(t_node *head, t_node *curr, int *pipes, int *pipe_pos)
{
	char	*path_list;

	if (curr->next && curr->content->num_redir == 0)
		pipes[(*pipe_pos) + 1] = pipes[(*pipe_pos) + 2];
	ft_dup2(&pipes[(*pipe_pos) + 1], &pipes[(*pipe_pos) + 2]);
	(*pipe_pos) += 2;
	if (is_built_in(curr->content->command))
		find_built(curr->content->args, curr->content->num_args,
			&(curr->var_list->env), &(curr->var_list->exp));
	path_list = get_path_list("PATH\0", curr->var_list->env);
	if (!path_list)
		ft_putstr_fd("variable not found", 2);
	if (!get_absolute_path(path_list, curr->content->command, curr))
		ft_putstr_fd("command not found", 2);
	if (execv(curr->content->command, curr->content->args) == -1)
		perror("execv: ");
	free_list(head);
}

int	execute_commands(t_node **head)
{
	int		pid;
	int		pipe_pos;
	int		*pipes;
	t_node	*tmp;

	pipe_pos = 0;
	// if (delete_backslash(*head))
	// 	return (1);
	if (!set_fd(head))
		return (1);
	if (!init_pipes(&pipes, *head))
		return (1);
	tmp = *head;
	while (tmp)
	{
		pid = fork();
		if (pid < 0)
			return (ft_putstr_fd("fork failed", 2), 1);
		else if (!pid)
			execute_child(*head, tmp, pipes, &pipe_pos);
		else
		{
			close_pipes(pipes, ft_len_node(*head));
			wait(NULL);
			//waitpid(-1, NULL, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}

// checker comandos para que no me entren caracteres especiales en el command
