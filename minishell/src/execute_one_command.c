#include "minishell.h"

char	*get_path_list(char *command, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(command, env->key))
			return (env->var);
		env = env->next;
	}
	ft_putstr_fd("path variable not found at env.", 2);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo\0") || !ft_strcmp(command, "cd\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "unset\0") || !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0"))
		return (1);
	return (0);
}

int	get_absolute_path(char *path_list, char *command, t_node *head)
{
	int		pos;
	char	*tmp;
	char	**split;
	char	*path;
	char	*absolute_dir;

	pos = -1;
	split = ft_split(path_list, ':');
	tmp = NULL;
	while (split && split[++pos])
	{
		path = split[pos];
		tmp = ft_strjoin(path, "/");
		absolute_dir = ft_strjoin(tmp, command);
		if (!access(absolute_dir, e_X_OK))
		{
			free(head->content->command);
			head->content->command = ft_strdup(absolute_dir);
			return (ft_free(split), free(absolute_dir), 1);
		}
		free(tmp);
		free(absolute_dir);
	}
	ft_putstr_fd("absolute path not found.", 2);
	return (ft_free(split), 0);
}

/* FUNCIONES QUE SIRVEN PARA OBTENER EL fd_in y out cuando tengo varias redirecciones

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

*/

int	excute_one_command(t_node **head, t_lists *lists)
{
	int		pid;
	char	*path_list;

	if (delete_backslash(head))
		return (1);
	if (is_built_in((*head)->content->command)) //restaurar el standard fd al final de la funcion con dup2
		return (find_built((*head)->content->args, (*head)->content->num_args,
				&(lists->env), &(lists->exp)));
	path_list = get_path_list("PATH\0", lists->env);
	if (!path_list)
		return (VARIABLE_NOT_FOUND);
	if (!get_absolute_path(path_list, (*head)->content->command, (*head)))
		return (COMMAND_NOT_FOUND);
	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("fork failed", 2), 1);
	else if (pid == 0)
	{
		if (execv((*head)->content->command, (*head)->content->args) == -1)
			return (perror("execv: "), 1);
		free_list(*head);
	}
	wait(NULL);
	return (0);
}
